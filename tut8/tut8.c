/*	Displaying bitmap graphics

	Tutorial 8 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=5u-Ftg3RnAE&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=8
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

#define WAITRAS1 68

#define SCREEN 0x60000
#define W 320
#define H 256
#define BPLSIZE (W * H) / 8

struct GfxBase *GfxBase;
struct copinit *oldCopinit;

// pointer to our bitmap "buffer"
UBYTE *screen = (UBYTE *)SCREEN;

/*	__attribute__((section("tut.MEMF_CHIP")))	
	seems to set the section as readonly	*/
UWORD copperlist[] =
{
	CMOVE(FMODE, 0),			// set FMODE to slow for AGA
	CMOVE(BPLCON0, 0x0200),		// no bitplanes, but need color burst

	CMOVE(DIWSTRT, 0x2c81),
	CMOVE(DIWSTOP, 0x2cc1),
	CMOVE(DDFSTRT, 0x38),
	CMOVE(DDFSTOP, 0xd0),
	CMOVE(BPL1MOD, 0),
	CMOVE(BPL2MOD, 0),

//CopBpLP:
	CMOVE(BPL1PTH, SCREEN >> 16),
	CMOVE(BPL1PTL, SCREEN & 0xffff),

	CMOVE(COLOR00,0x349),
	CWAIT(0x2b07,0xfffe),
	CMOVE(COLOR00,0x56c),
	CWAIT(0x2c07,0xfffe),
	CMOVE(COLOR00,0x113),
	CMOVE(BPLCON0,0x1200),
	CMOVE(COLOR01,0x349),		// pixel colour

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

	// copy "random" data to our buffer using H beam value
	for(UWORD index = 0; index < BPLSIZE; index++)
	{
		screen[index] = GETBYTE_LO(custom->vhposr);
	}

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