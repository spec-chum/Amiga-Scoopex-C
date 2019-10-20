/*	Make a rasterline

	Tutorial 2 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=bqT1jsPyUGw&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=2
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
	// loop until mouse clicked
	while(ciaa->ciapra & CIAF_GAMEPORT0)
	{
		// do literally nothing until we reach yPos 0xac
		while(HIBYTE(custom->vhposr) != 0xac)
		{}
		custom->color[0] = 0xfff;	// bg white

		// now do nothing until we're not on yPos 0xac
		while(HIBYTE(custom->vhposr) == 0xac)
		{}
		custom->color[0] = 0x116;	// bg blue
	}

    return 0;
}
