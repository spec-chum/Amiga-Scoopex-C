/*	Deluxe Paint and IFFconv

	Tutorial 10 of Scoopex's incredible Amiga Hardware Programming Series on YouTube

	https://www.youtube.com/watch?v=5sftmTUArm8&list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW&index=10

	Only one small change on this one from tut9, as the video is mainly about using DPaint.

	If you don't fancy creating your art on the Amiga, GrafX2 http://grafx2.chez.com/ comes highly recommended,
	this can save as IFF as well as many other retro friendly formats.

	For IFFconv I've included, in the tutorials root folder, KingCon from Lemon's excellent toolchain:
	https://www.pouet.net/prod.php?which=65625

	There is an exe file in there, compiled with VS2019, but I've included the source too.

	A help file is also included with all the options, but to get a bit-identical raw image to photon's raw use:
	KingCon sky.iff sky.178x67x3.raw -F=3 -T -I

	Then just remove the .BPL from the outputted filename.
*/

#include "support/gcc8_c_support.h"

#include <proto/exec.h>
#include <proto/graphics.h>
#include <hardware/cia.h>
#include <hardware/custom.h>
#include <hardware/dmabits.h>
#include <graphics/gfxbase.h>

#include "../headers/structs.h"
#include "../headers/custom_defines.h"
#include "../headers/helpers.h"

#define WAITRAS1 45 * 4
#define SPRP 12 * 2

#define SCREEN 0x60000
#define W 320
#define H 256
#define BPLSIZE (W * H) / 8

struct GfxBase *GfxBase;
struct copinit *oldCopinit;

// pointer to our bitmap "buffer"
UBYTE *screen = (UBYTE *)SCREEN;

__attribute__((section("tut.MEMF_CHIP"))) UWORD spr[] =
{
	0x2c40, 0x3c00, // Vstart.b,Hstart/2.b,Vstop.b,%A0000SEH

	0b0000011111000000, 0b0000000000000000,
	0b0001111111110000, 0b0000000000000000,
	0b0011111111111000, 0b0000000000000000,
	0b0111111111111100, 0b0000000000000000,
	0b0110011111001100, 0b0001100000110000,
	0b1110011111001110, 0b0001100000110000,
	0b1111111111111110, 0b0000000000000000,
	0b1111111111111110, 0b0000000000000000,
	0b1111111111111110, 0b0010000000001000,
	0b1111111111111110, 0b0001100000110000,
	0b0111111111111100, 0b0000011111000000,
	0b0111111111111100, 0b0000000000000000,
	0b0011111111111000, 0b0000000000000000,
	0b0001111111110000, 0b0000000000000000,
	0b0000011111000000, 0b0000000000000000,
	0b0000000000000000, 0b0000000000000000,

	0, 0
};

__attribute__((section("tut.MEMF_CHIP"))) UWORD nullSpr[] =
{
	0x2a20, 0x2b00,
	0, 0,
	0, 0
};

__attribute__((section("tut.MEMF_CHIP"))) UWORD copperlist[] =
{
	CMOVE(FMODE, 0),			// set FMODE to slow for AGA
	CMOVE(BPLCON0, 0x0200),		// no bitplanes, but need color burst

	CMOVE(DIWSTRT, 0x2c81),
	CMOVE(DIWSTOP, 0x2cc1),

	CMOVE(DDFSTRT, 0x38),
	CMOVE(DDFSTOP, 0xd0),

	CMOVE(BPL1MOD, 0),
	CMOVE(BPL2MOD, 0),

	CMOVE(BPLCON1, 0),

	CMOVE(COLOR17, 0xe22),
	CMOVE(COLOR18, 0xff0),
	CMOVE(COLOR19, 0xfff),

//SprP:
	CMOVE(SPR0PTH, 0),
	CMOVE(SPR0PTL, 0),
        
	CMOVE(SPR1PTH, 0),
	CMOVE(SPR1PTL, 0),
        
	CMOVE(SPR2PTH, 0),
	CMOVE(SPR2PTL, 0),
        
	CMOVE(SPR3PTH, 0),
	CMOVE(SPR3PTL, 0),
        
	CMOVE(SPR4PTH, 0),
	CMOVE(SPR4PTL, 0),
        
	CMOVE(SPR5PTH, 0),
	CMOVE(SPR5PTL, 0),
        
	CMOVE(SPR6PTH, 0),
	CMOVE(SPR6PTL, 0),
        
	CMOVE(SPR7PTH, 0),
	CMOVE(SPR7PTL, 0),

//CopBpLP:
	CMOVE(BPL1PTH, SCREEN >> 16),
	CMOVE(BPL1PTL, SCREEN & 0xffff),

	CMOVE(COLOR00,0x349),

	CWAIT(0x2b07,0xfffe),
	CMOVE(COLOR00,0x56c),

	CWAIT(0x2c07,0xfffe),	
	CMOVE(COLOR00,0x113),

//LogoPal
	CMOVE(COLOR00, 0x667),
	CMOVE(COLOR01, 0xddd),
	CMOVE(COLOR02, 0x833),
	CMOVE(COLOR03, 0x334),
	CMOVE(COLOR04, 0xa88),
	CMOVE(COLOR05, 0x99a),
	CMOVE(COLOR06, 0x556),
	CMOVE(COLOR07, 0x633),

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

void WaitRaster(ULONG raster)
{
	raster <<= 8;
	raster &= 0x1ff00;

	// not pretty, but creates pretty much same code as the asm source (MOVE.L)
	while(raster != (GETLONG(custom->vposr) & 0x1ff00))
	{}
}

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
	UWORD oldDMA = custom->dmaconr;

	// wait for EOF
	WaitRaster(0x138);

	// disable all interrupts and DMA
	custom->intena = 0x7fff;
	custom->intreq = 0x7fff;
	custom->intreq = 0x7fff;	// needed twice?  Works fine with 1
	custom->dmacon = 0x7fff;

	// set required bits of DMA (0x87e0)
	custom->dmacon = DMAF_SETCLR | DMAF_MASTER | DMAF_RASTER | DMAF_BLITHOG | DMAF_SPRITE | DMAF_BLITTER | DMAF_COPPER;

	// copy "random" data to our buffer using H beam value
	for(UWORD index = 0; index < BPLSIZE; index++)
	{
		screen[index] = GETBYTE_LO(custom->vhposr);
	}

	// set actual sprite pointer
	copperlist[SPRP + 1] = (ULONG)spr >> 16;
	copperlist[SPRP + 3] = (ULONG)spr & 0xffff;

	// set others to nullSpr so they don't display
	for(UWORD index = 0; index < 7; index++)
	{
		// looks complex but gets compiled into 2 single move.w instructions per loop
		copperlist[(SPRP + (index * 4) + 5)] = (ULONG)nullSpr >> 16;
		copperlist[(SPRP + (index * 4) + 7)] = (ULONG)nullSpr & 0xffff;
	}

	// initiate our copper
	custom->cop1lc = (ULONG)copperlist;

	// loop until mouse clicked
	while(ciaa->ciapra & CIAF_GAMEPORT0)
	{
		// wait for start of frame ** wframe **
		if((GETBYTE_LO(custom->vposr) & 1) == 0 && GETBYTE_HI(custom->vhposr) == 0x2a)
		{
			while(GETBYTE_HI(custom->vhposr) == 0x2a)
			{ } // wframe2

			// move sprite
			((volatile UBYTE *)spr)[1]++;
			
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
				((UBYTE *)copperlist)[WAITRAS1 + (waitras * 8)] = yPos + waitras;
			}
		}
	}

	// restore DMA
	custom->dmacon = 0x7fff;
	custom->dmacon = oldDMA | DMAF_SETCLR | DMAF_MASTER;

	// restore original copper
	custom->cop1lc = (ULONG)oldCopinit;

	// restore interrupts
	custom->intena = oldInt | 0xc000;

	return 0;
}