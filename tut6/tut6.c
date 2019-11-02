/*	Understanding the Raster

	Tutorial 6 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=ZxnSe1BeNzA&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=6
*/

#include "support/gcc8_c_support.h"

#include <proto/exec.h>
#include <proto/graphics.h>
#include <hardware/cia.h>
#include <hardware/custom.h>
#include <graphics/gfxbase.h>

#include "../headers/structs.h"
#include "../headers/custom_defines.h"
#include "../headers/helpers.h"

#define WAITRAS1 28
#define WAITRAS2 36

struct GfxBase *GfxBase;
struct copinit *oldCopinit;


/*	__attribute__((section("tut.MEMF_CHIP")))	
	seems to set the section as readonly	*/
UWORD copperlist[] =
{
	CMOVE(FMODE, 0x0000),		// set FMODE to slow for AGA
	CMOVE(BPLCON0, 0x0200),		// no bitplanes, but need color burst

	CMOVE(COLOR00, 0x0349),
	CWAIT(0x2b07, 0xfffe),
	CMOVE(COLOR00, 0x056c),
	CWAIT(0x2c07, 0xfffe),
	CMOVE(COLOR00, 0x0113),

// waitras1:
	CWAIT(0x8007, 0xfffe),
	CMOVE(COLOR00, 0x0fff),

// waitras2:
	CWAIT(0x8107, 0xfffe),
	CMOVE(COLOR00, 0x0113),

	CWAIT(0xffdf, 0xfffe),
	CWAIT(0x2c07, 0xfffe),
	CMOVE(COLOR00, 0x056c),
	CWAIT(0x2d07, 0xfffe),
	CMOVE(COLOR00, 0x0349),

	CEND		
};

int main()
{
	SysBase = *(struct ExecBase**)4L;

	// place our copperlist in chipmem
	UBYTE *clptr = AllocMem(sizeof(copperlist), MEMF_CHIP);
	CopyMem(copperlist, clptr, sizeof(copperlist));

	// open gfx lib and save original copperlist
	GfxBase = (struct GfxBase*)OldOpenLibrary("graphics.library");
	oldCopinit = GfxBase->copinit;
	CloseLibrary((struct Library *)GfxBase);
	
	// line starting position
	UWORD yPos = 0xac;

	// line direction
	WORD yDir = 1;

	// Save interrupts and DMA
	UWORD oldInt = custom->intenar;

	// disable all interrupts
	custom->intena = 0x7fff;

	// initiate our copper
	custom->cop1lc = (ULONG)clptr;

	// loop until mouse clicked
	while(ciaa->ciapra & CIAF_GAMEPORT0)
	{
		// wait for start of frame - wframe
		if((GETBYTE_LO(custom->vposr) & 1) == 0 && GETBYTE_HI(custom->vhposr) == 0x2a)
		{
			while(GETBYTE_HI(custom->vhposr) == 0x2a)
			{ } // wframe2
			
			// update line y position
			yPos += yDir;

			// bounce line
			if(yPos > 0xf0 || yPos < 0x40)
			{
				yDir = -yDir;
			}

			clptr[WAITRAS1] = yPos;
			clptr[WAITRAS2] = yPos + 5;
		}
	}

	// restore original copper
	custom->cop1lc = (ULONG)oldCopinit;

	// free copperlist memory
	FreeMem(clptr, sizeof(copperlist));

	// restore interrupts
	custom->intena = oldInt | 0xc000;

	return 0;
}