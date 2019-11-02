/*	Understanding the Memory

	Tutorial 7 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=ZPJW3wIfL4I&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=7
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

struct GfxBase *GfxBase;
struct copinit *oldCopinit;

/*	__attribute__((section("tut.MEMF_CHIP")))	
	seems to set the section as readonly	*/
UWORD copperlist[] =
{
	CMOVE(FMODE, 0x000),		// set FMODE to slow for AGA
	CMOVE(BPLCON0, 0x200),		// no bitplanes, but need color burst

	CMOVE(COLOR00, 0x349),
	CWAIT(0x2b07, 0xfffe),
	CMOVE(COLOR00, 0x56c),
	CWAIT(0x2c07, 0xfffe),
	CMOVE(COLOR00, 0x113),

// waitras1:
	CWAIT(0x8007, 0xfffe),
	CMOVE(COLOR00, 0x055),

// waitras2:
	CWAIT(0x8107, 0xfffe),
	CMOVE(COLOR00, 0x0aa),

// waitras3:
	CWAIT(0x8207, 0xfffe),
	CMOVE(COLOR00, 0x0ff),

// waitras4:
	CWAIT(0x8307, 0xfffe),
	CMOVE(COLOR00, 0x0aa),

// waitras5:
	CWAIT(0x8407, 0xfffe),
	CMOVE(COLOR00, 0x055),

// waitras6:
	CWAIT(0x8507, 0xfffe),
	CMOVE(COLOR00, 0x113),

	CWAIT(0xffdf, 0xfffe),
	CWAIT(0x2c07, 0xfffe),
	CMOVE(COLOR00, 0x56c),
	CWAIT(0x2d07, 0xfffe),
	CMOVE(COLOR00, 0x349),

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
		// wait for start of frame ** wframe **
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

			// dynamically update all waitras values
			for(UWORD waitras = 0; waitras < 6; waitras++)
			{
				clptr[WAITRAS1 + (waitras * 8)] = yPos + waitras;
			}
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