/*	System OFF, please

	Tutorial 4 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=DrtIjvqruOI&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=4
*/

#include "support/gcc8_c_support.h"

#include <hardware/cia.h>
#include <hardware/custom.h>

#include "../headers/helpers.h"

// Not used here, but needed by GCC 8
struct ExecBase *SysBase;

volatile struct Custom *custom = (struct Custom *)0xdff000;
volatile struct CIA *ciaa  = (struct CIA *)0xbfe001;

int main()
{
	// line starting position
	UWORD yPos = 0xac;

	// line direction
	WORD yDir = 1;

	// Save interrupts and DMA
	UWORD oldInt = custom->intenar;

	// disable all interrupts
	custom->intena = 0x7fff;

	// loop until mouse clicked
	while(ciaa->ciapra & CIAF_GAMEPORT0)
	{
		// wait for start of frame
		if((custom->vposr & 1) == 0 && HIBYTE(custom->vhposr) == 0x2c)
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
			while(HIBYTE(custom->vhposr) != yPos)
			{}
			custom->color[0] = 0xfff;	// bg white

			// now do nothing until we're not on yPos
			while(HIBYTE(custom->vhposr) == yPos)
			{}
			custom->color[0] = 0x116;	// bg blue
		}
	}

	// restore interrupts and DMA
	custom->intena = oldInt | 0xc000;

	return 0;
}