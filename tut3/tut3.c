/*	Move that rasterline

	Tutorial 3 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=dVLnL7_jtu0&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=3
*/

#include "support/gcc8_c_support.h"

#include <hardware/cia.h>
#include <hardware/custom.h>

#include "../headers/structs.h"
#include "../headers/helpers.h"

int main()
{
	// line starting position
	UWORD yPos = 0xac;

	// line direction
	WORD yDir = 1;

	// loop until mouse clicked
	while(ciaa->ciapra & CIAF_GAMEPORT0)
	{
		// wait for start of frame
		if(GETBYTE_HI(custom->vhposr) == 0xff)
		{
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
			custom->color[0] = 0x116;	// bg blue
		}
	}

    return 0;
}
