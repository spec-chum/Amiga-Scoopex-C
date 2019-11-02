/*	Make a rasterline

	Tutorial 2 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=bqT1jsPyUGw&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=2
*/

#include "support/gcc8_c_support.h"

#include <hardware/cia.h>
#include <hardware/custom.h>

#include "../headers/structs.h"
#include "../headers/helpers.h"

int main()
{
	// loop until mouse clicked
	while(ciaa->ciapra & CIAF_GAMEPORT0)
	{
		// do literally nothing until we reach yPos 0xac
		while(GETBYTE_HI(custom->vhposr) != 0xac)
		{}
		custom->color[0] = 0xfff;	// bg white

		// now do nothing until we're not on yPos 0xac
		while(GETBYTE_HI(custom->vhposr) == 0xac)
		{}
		custom->color[0] = 0x116;	// bg blue
	}

    return 0;
}
