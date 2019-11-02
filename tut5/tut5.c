/*	One copper to rule to screen

	Tutorial 5 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=9OIbSXZmuBE&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=5
*/

#include "support/gcc8_c_support.h"

#include <proto/exec.h>
#include <proto/graphics.h>
#include <hardware/cia.h>
#include <hardware/custom.h>
#include <graphics/gfxbase.h>

#include "../headers/structs.h"
#include "../headers/helpers.h"

struct GfxBase *GfxBase;
struct copinit *oldCopinit;

__attribute__((section("tut.MEMF_CHIP"))) UWORD copperlist[] =
{
		0x0100, 0x0200,		// disable bitplanes but leave color burst
		
		0xffff, 0xfffe		// end list
};

int main()
{
	SysBase = *((struct ExecBase**)4L);

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
	custom->cop1lc = (ULONG)copperlist;

	// loop until mouse clicked
	while(ciaa->ciapra & CIAF_GAMEPORT0)
	{
		// wait for start of frame
		if((GETBYTE_LO(custom->vposr) & 1) == 0 && GETBYTE_HI(custom->vhposr) == 0x2c)
		{
			custom->color[0] = 0;	// bg black

			// update line y position
			yPos += yDir;

			// bounce line
			if(yPos > 0xf0 || yPos < 0x40)
			{
				yDir = -yDir;
			}

			// do literally nothing until we reach yPos
			while(GETBYTE_HI(custom->vhposr) != yPos)
			{}
			custom->color[0] = 0xfff;	// bg white

			// now do nothing until we're not on yPos
			while(GETBYTE_HI(custom->vhposr) == yPos)
			{}
			custom->color[0] = 0;	// bg black
		}
	}

	// restore original copper
	custom->cop1lc = (ULONG)oldCopinit;

	// restore interrupts and DMA
	custom->intena = oldInt | 0xc000;

	return 0;
}