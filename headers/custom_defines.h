/*		Custom Chip Defines

		Access Key:
		R: READ    W: WRITE    O: OCS    E: ECS    A: AGA
*/

#define CUSTOMBASE	0xdff000	// Custom chip base address

/*		Name		Address		Access	O	E	A	Description */
#define BLTDDAT		0x000		//	ER	*	*	*	Blitter dest. early read (dummy address)
#define DMACONR		0x002		//	R	*	*	*	Dma control (and blitter status) read
#define VPOSR		0x004		//	R	*	*	*	Read vertical most sig. bits (and frame flop)
#define VHPOSR		0x006		//	R	*	*	*	Read vert and horiz position of beam
#define DSKDATR		0x008		//	ER	*	*	*	Disk data early read (dummy address)
#define JOY0DAT		0x00A		//	R	*	*	*	Joystick-mouse 0 data (vert, horiz)
#define JOY1DAT		0x00C		//	R	*	*	*	Joystick-mouse 1 data (vert, horiz)
#define CLXDAT		0x00E		//	R	*	*	*	Collision data reg. (read and clear)
#define ADKCONR		0x010		//	R	*	*	*	Audio,disk control register read
#define POT0DAT		0x012		//	R	*	*	*	Pot counter data left pair (vert, horiz)
#define POT1DAT		0x014		//	R	*	*	*	Pot counter data right pair (vert, horiz)
#define POTINP		0x016		//	R	*	*	*	Pot pin data read
#define SERDATR		0x018		//	R	*	*	*	Serial port data and status read
#define DSKBYTR		0x01A		//	R	*	*	*	Disk data byte and status read
#define INTENAR		0x01C		//	R	*	*	*	Interrupt enable bits read
#define INTREQR		0x01E		//	R	*	*	*	Interrupt request bits read
#define DSKPTH		0x020		//	W	*	*	*	Disk pointer (high 5 bits, was 3 bits)
#define DSKPTL		0x022		//	W	*	*	*	Disk pointer (low 15 bits)
#define DSKLEN		0x024		//	W	*	*	*	Disk length
#define DSKDAT		0x026		//	W	*	*	*	Disk DMA data write
#define REFPTR		0x028		//	W	*	*	*	Refresh pointer
#define VPOSW		0x02A		//	W	*	*	*	Write vert most sig. bits (and frame flop)
#define VHPOSW		0x02C		//	W	*	*	*	Write vert and horiz pos of beam
#define COPCON		0x02E		//	W	*	*	*	Coprocessor control
#define SERDAT		0x030		//	W	*	*	*	Serial port data and stop bits write
#define SERPER		0x032		//	W	*	*	*	Serial port period and control
#define POTGO		0x034		//	W	*	*	*	Pot count start,pot pin drive enable data
#define JOYTEST		0x036		//	W	*	*	*	Write to all 4 joystick-mouse counters at once
#define STREQU		0x038		//	S	*	*	*	Strobe for horiz sync with VB and EQU
#define STRVBL		0x03A		//	S	*	*	*	Strobe for horiz sync with VB (vert blank)
#define STRHOR		0x03C		//	S	*	*	*	Strobe for horiz sync
#define STRLONG		0x03E		//	S	*	*	*	Strobe for identification of long horiz line
#define BLTCON0		0x040		//	W	*	*	*	Blitter control register 0
#define BLTCON1		0x042		//	W	*	*	*	Blitter control register 1
#define BLTAFWM		0x044		//	W	*	*	*	Blitter first word mask for source A
#define BLTALWM		0x046		//	W	*	*	*	Blitter last word mask for source A
#define BLTCPTH		0x048		//	W	*	*	*	Blitter pointer to source C (high 5 bits, was 3 bits)
#define BLTCPTL		0x04A		//	W	*	*	*	Blitter pointer to source C (low 15 bits)
#define BLTBPTH		0x04C		//	W	*	*	*	Blitter pointer to source B (high 5 bits, was 3 bits)
#define BLTBPTL		0x04E		//	W	*	*	*	Blitter pointer to source B (low 15 bits)
#define BLTAPTH		0x050		//	W	*	*	*	Blitter pointer to source A (high 5 bits, was 3 bits)
#define BLTAPTL		0x052		//	W	*	*	*	Blitter pointer to source A (low 15 bits)
#define BLTDPTH		0x054		//	W	*	*	*	Blitter pointer to dest D (high 5 bits, was 3 bits)
#define BLTDPTL		0x056		//	W	*	*	*	Blitter pointer to dest D (low 15 bits)
#define BLTSIZE		0x058		//	W	*	*	*	Blitter start and size (win/width,height)
#define BLTCON0L	0x05A		//	W		*	*	Blitter control 0, lower 8 bits (minterms)
#define BLTSIZV		0x05C		//	W		*	*	Blitter V size (for 15 bit vertical size)
#define BLTSIZH		0x05E		//	W		*	*	Blitter H size and start (for 11 bit H size)
#define BLTCMOD		0x060		//	W	*	*	*	Blitter modulo for source C
#define BLTBMOD		0x062		//	W	*	*	*	Blitter modulo for source B
#define BLTAMOD		0x064		//	W	*	*	*	Blitter modulo for source A
#define BLTDMOD		0x066		//	W	*	*	*	Blitter modulo for dest D
#define BLTCDAT		0x070		//	W	*	*	*	Blitter source C data register
#define BLTBDAT		0x072		//	W	*	*	*	Blitter source B data register
#define BLTADAT		0x074		//	W	*	*	*	Blitter source A data register
#define SPRHDAT		0x078		//	W		*	*	Ext. logic UHRES sprite pointer and data identifier
#define BPLHDAT		0x07A		//	W		*	*	Ext. logic UHRES bit plane identifier
#define DENISEID	0x07C		//	R		*	*	Chip revision level for Denise/Lisa (video out chip)
#define DSKSYNC		0x07E		//	W	*	*	*	Disk sync pattern reg for disk read
#define COP1LCH		0x080		//	W	*	*	*	Coprocessor 1st location (high 5 bits,was 3 bits)
#define COP1LCL		0x082		//	W	*	*	*	Coprocessor 1st location (low 15 bits)
#define COP2LCH		0x084		//	W	*	*	*	Coprocessor 2nd location(high 5 bits,was 3 bits)
#define COP2LCL		0x086		//	W	*	*	*	Coprocessor 2nd location (low 15 bits)
#define COPJMP1		0x088		//	S	*	*	*	Coprocessor restart at 1st location
#define COPJMP2		0x08A		//	S	*	*	*	Coprocessor restart at 2nd location
#define COPINS		0x08C		//	W	*	*	*	Coprocessor inst fetch identify
#define DIWSTRT		0x08E		//	W	*	*	*	Display window start (upper left vert,horiz pos)
#define DIWSTOP		0x090		//	W	*	*	*	Display window stop (lower right vert,horiz pos)
#define DDFSTRT		0x092		//	W	*	*	*	Display bit plane data fetch start,horiz pos
#define DDFSTOP		0x094		//	W	*	*	*	Display bit plane data fetch stop,horiz pos
#define DMACON		0x096		//	W	*	*	*	DMA control write (clear or set)
#define CLXCON		0x098		//	W	*	*	*	Collision control
#define INTENA		0x09A		//	W	*	*	*	Interrupt enable bits (clear or set bits)
#define INTREQ		0x09C		//	W	*	*	*	Interrupt request bits (clear or set bits)
#define ADKCON		0x09E		//	W	*	*	*	Audio,disk,UART control
#define AUD0LCH		0x0A0		//	W	*	*	*	Audio channel 0 location (high 5 bits was 3 bits)
#define AUD0LCL		0x0A2		//	W	*	*	*	Audio channel 0 location (low 15 bits)
#define AUD0LEN		0x0A4		//	W	*	*	*	Audio channel 0 length
#define AUD0PER		0x0A6		//	W	*	*	*	Audio channel 0 period
#define AUD0VOL		0x0A8		//	W	*	*	*	Audio channel 0 volume
#define AUD0DAT		0x0AA		//	W	*	*	*	Audio channel 0 data
#define AUD1LCH		0x0B0		//	W	*	*	*	Audio channel 1 location (high 5 bits was 3 bits)
#define AUD1LCL		0x0B2		//	W	*	*	*	Audio channel 1 location (low 15 bits)
#define AUD1LEN		0x0B4		//	W	*	*	*	Audio channel 1 length
#define AUD1PER		0x0B6		//	W	*	*	*	Audio channel 1 period
#define AUD1VOL		0x0B8		//	W	*	*	*	Audio channel 1 volume
#define AUD1DAT		0x0BA		//	W	*	*	*	Audio channel 1 data
#define AUD2LCH		0x0C0		//	W	*	*	*	Audio channel 2 location (high 5 bits was 3 bits)
#define AUD2LCL		0x0C2		//	W	*	*	*	Audio channel 2 location (low 15 bits)
#define AUD2LEN		0x0C4		//	W	*	*	*	Audio channel 2 length
#define AUD2PER		0x0C6		//	W	*	*	*	Audio channel 2 period
#define AUD2VOL		0x0C8		//	W	*	*	*	Audio channel 2 volume
#define AUD2DAT		0x0CA		//	W	*	*	*	Audio channel 2 data
#define AUD3LCH		0x0D0		//	W	*	*	*	Audio channel 3 location (high 5 bits was 3 bits)
#define AUD3LCL		0x0D2		//	W	*	*	*	Audio channel 3 location (low 15 bits)
#define AUD3LEN		0x0D4		//	W	*	*	*	Audio channel 3 length
#define AUD3PER		0x0D6		//	W	*	*	*	Audio channel 3 period
#define AUD3VOL		0x0D8		//	W	*	*	*	Audio channel 3 volume
#define AUD3DAT		0x0DA		//	W	*	*	*	Audio channel 3 data
#define BPL1PTH		0x0E0		//	W	*	*	*	Bitplane pointer 1 (high 5 bits was 3 bits)
#define BPL1PTL		0x0E2		//	W	*	*	*	Bitplane pointer 1 (low 15 bits)
#define BPL2PTH		0x0E4		//	W	*	*	*	Bitplane pointer 2 (high 5 bits was 3 bits)
#define BPL2PTL		0x0E6		//	W	*	*	*	Bitplane pointer 2 (low 15 bits)
#define BPL3PTH		0x0E8		//	W	*	*	*	Bitplane pointer 3 (high 5 bits was 3 bits)
#define BPL3PTL		0x0EA		//	W	*	*	*	Bitplane pointer 3 (low 15 bits)
#define BPL4PTH		0x0EC		//	W	*	*	*	Bitplane pointer 4 (high 5 bits was 3 bits)
#define BPL4PTL		0x0EE		//	W	*	*	*	Bitplane pointer 4 (low 15 bits)
#define BPL5PTH		0x0F0		//	W	*	*	*	Bitplane pointer 5 (high 5 bits was 3 bits)
#define BPL5PTL		0x0F2		//	W	*	*	*	Bitplane pointer 5 (low 15 bits)
#define BPL6PTH		0x0F4		//	W	*	*	*	Bitplane pointer 6 (high 5 bits was 3 bits)
#define BPL6PTL		0x0F6		//	W	*	*	*	Bitplane pointer 6 (low 15 bits)
#define BPL7PTH		0x0F8		//	W			*	Bitplane pointer 7 (high 5 bits was 3 bits)
#define BPL7PTL		0x0FA		//	W			*	Bitplane pointer 7 (low 15 bits)
#define BPL8PTH		0x0FC		//	W			*	Bitplane pointer 8 (high 5 bits was 3 bits)
#define BPL8PTL		0x0FE		//	W			*	Bitplane pointer 8 (low 15 bits)
#define BPLCON0		0x100		//	W	*	*	*	Bitplane control (miscellaneous control bits)
#define BPLCON1		0x102		//	W	*	*	*	Bitplane control (scroll value)
#define BPLCON2		0x104		//	W	*	*	*	Bitplane control (video priority control)
#define BPLCON3		0x106		//	W	*	*	*	Bitplane control (enhanced features)
#define BPL1MOD		0x108		//	W	*	*	*	Bitplane modulo (odd planes)
#define BPL2MOD		0x10A		//	W	*	*	*	Bitplane modulo (even planes)
#define BPLCON4		0x10C		//	W			*	Bitplane control (bitplane and sprite-masks)
#define CLXCON2		0x10E		//	W			*	Extended collision control
#define BPL1DAT		0x110		//	W	*	*	*	Bitplane 1 data (parallel to serial convert)
#define BPL2DAT		0x112		//	W	*	*	*	Bitplane 2 data (parallel to serial convert)
#define BPL3DAT		0x114		//	W	*	*	*	Bitplane 3 data (parallel to serial convert)
#define BPL4DAT		0x116		//	W	*	*	*	Bitplane 4 data (parallel to serial convert)
#define BPL5DAT		0x118		//	W	*	*	*	Bitplane 5 data (parallel to serial convert)
#define BPL6DAT		0x11A		//	W	*	*	*	Bitplane 6 data (parallel to serial convert)
#define BPL7DAT		0x11C		//	W			*	Bitplane 7 data (parallel to serial convert)
#define BPL8DAT		0x11E		//	W			*	Bitplane 8 data (parallel to serial convert)
#define SPR0PTH		0x120		//	W	*	*	*	Sprite 0 pointer (high 5 bits was 3 bits)
#define SPR0PTL		0x122		//	W	*	*	*	Sprite 0 pointer (low 15 bits)
#define SPR1PTH		0x124		//	W	*	*	*	Sprite 1 pointer (high 5 bits was 3 bits)
#define SPR1PTL		0x126		//	W	*	*	*	Sprite 1 pointer (low 15 bits)
#define SPR2PTH		0x128		//	W	*	*	*	Sprite 2 pointer (high 5 bits was 3 bits)
#define SPR2PTL		0x12A		//	W	*	*	*	Sprite 2 pointer (low 15 bits)
#define SPR3PTH		0x12C		//	W	*	*	*	Sprite 3 pointer (high 5 bits was 3 bits)
#define SPR3PTL		0x12E		//	W	*	*	*	Sprite 3 pointer (low 15 bits)
#define SPR4PTH		0x130		//	W	*	*	*	Sprite 4 pointer (high 5 bits was 3 bits)
#define SPR4PTL		0x132		//	W	*	*	*	Sprite 4 pointer (low 15 bits)
#define SPR5PTH		0x134		//	W	*	*	*	Sprite 5 pointer (high 5 bits was 3 bits)
#define SPR5PTL		0x136		//	W	*	*	*	Sprite 5 pointer (low 15 bits)
#define SPR6PTH		0x138		//	W	*	*	*	Sprite 6 pointer (high 5 bits was 3 bits)
#define SPR6PTL		0x13A		//	W	*	*	*	Sprite 6 pointer (low 15 bits)
#define SPR7PTH		0x13C		//	W	*	*	*	Sprite 7 pointer (high 5 bits was 3 bits)
#define SPR7PTL		0x13E		//	W	*	*	*	Sprite 7 pointer (low 15 bits)
#define SPR0POS		0x140		//	W	*	*	*	Sprite 0 vert,horiz start pos data
#define SPR0CTL		0x142		//	W	*	*	*	Sprite 0 position and control data
#define SPR0DATA	0x144		//	W	*	*	*	Sprite 0 image data register A
#define SPR0DATB	0x146		//	W	*	*	*	Sprite 0 image data register B
#define SPR1POS		0x148		//	W	*	*	*	Sprite 1 vert,horiz start pos data
#define SPR1CTL		0x14A		//	W	*	*	*	Sprite 1 position and control data
#define SPR1DATA	0x14C		//	W	*	*	*	Sprite 1 image data register A
#define SPR1DATB	0x14E		//	W	*	*	*	Sprite 1 image data register B
#define SPR2POS		0x150		//	W	*	*	*	Sprite 2 vert,horiz start pos data
#define SPR2CTL		0x152		//	W	*	*	*	Sprite 2 position and control data
#define SPR2DATA	0x154		//	W	*	*	*	Sprite 2 image data register A
#define SPR2DATB	0x156		//	W	*	*	*	Sprite 2 image data register B
#define SPR3POS		0x158		//	W	*	*	*	Sprite 3 vert,horiz start pos data
#define SPR3CTL		0x15A		//	W	*	*	*	Sprite 3 position and control data
#define SPR3DATA	0x15C		//	W	*	*	*	Sprite 3 image data register A
#define SPR3DATB	0x15E		//	W	*	*	*	Sprite 3 image data register B
#define SPR4POS		0x160		//	W	*	*	*	Sprite 4 vert,horiz start pos data
#define SPR4CTL		0x162		//	W	*	*	*	Sprite 4 position and control data
#define SPR4DATA	0x164		//	W	*	*	*	Sprite 4 image data register A
#define SPR4DATB	0x166		//	W	*	*	*	Sprite 4 image data register B
#define SPR5POS		0x168		//	W	*	*	*	Sprite 5 vert,horiz start pos data
#define SPR5CTL		0x16A		//	W	*	*	*	Sprite 5 position and control data
#define SPR5DATA	0x16C		//	W	*	*	*	Sprite 5 image data register A
#define SPR5DATB	0x16E		//	W	*	*	*	Sprite 5 image data register B
#define SPR6POS		0x170		//	W	*	*	*	Sprite 6 vert,horiz start pos data
#define SPR6CTL		0x172		//	W	*	*	*	Sprite 6 position and control data
#define SPR6DATA	0x174		//	W	*	*	*	Sprite 6 image data register A
#define SPR6DATB	0x176		//	W	*	*	*	Sprite 6 image data register B
#define SPR7POS		0x178		//	W	*	*	*	Sprite 7 vert,horiz start pos data
#define SPR7CTL		0x17A		//	W	*	*	*	Sprite 7 position and control data
#define SPR7DATA	0x17C		//	W	*	*	*	Sprite 7 image data register A
#define SPR7DATB	0x17E		//	W	*	*	*	Sprite 7 image data register B
#define COLOR00		0x180		//	W	*	*	*	Color table 0
#define COLOR01		0x182		//	W	*	*	*	Color table 1
#define COLOR02		0x184		//	W	*	*	*	Color table 2
#define COLOR03		0x186		//	W	*	*	*	Color table 3
#define COLOR04		0x188		//	W	*	*	*	Color table 4
#define COLOR05		0x18A		//	W	*	*	*	Color table 5
#define COLOR06		0x18C		//	W	*	*	*	Color table 6
#define COLOR07		0x18E		//	W	*	*	*	Color table 7
#define COLOR08		0x190		//	W	*	*	*	Color table 8
#define COLOR09		0x192		//	W	*	*	*	Color table 9
#define COLOR10		0x194		//	W	*	*	*	Color table 10
#define COLOR11		0x196		//	W	*	*	*	Color table 11
#define COLOR12		0x198		//	W	*	*	*	Color table 12
#define COLOR13		0x19A		//	W	*	*	*	Color table 13
#define COLOR14		0x19C		//	W	*	*	*	Color table 14
#define COLOR15		0x19E		//	W	*	*	*	Color table 15
#define COLOR16		0x1A0		//	W	*	*	*	Color table 16
#define COLOR17		0x1A2		//	W	*	*	*	Color table 17
#define COLOR18		0x1A4		//	W	*	*	*	Color table 18
#define COLOR19		0x1A6		//	W	*	*	*	Color table 19
#define COLOR20		0x1A8		//	W	*	*	*	Color table 20
#define COLOR21		0x1AA		//	W	*	*	*	Color table 21
#define COLOR22		0x1AC		//	W	*	*	*	Color table 22
#define COLOR23		0x1AE		//	W	*	*	*	Color table 23
#define COLOR24		0x1B0		//	W	*	*	*	Color table 24
#define COLOR25		0x1B2		//	W	*	*	*	Color table 25
#define COLOR26		0x1B4		//	W	*	*	*	Color table 26
#define COLOR27		0x1B6		//	W	*	*	*	Color table 27
#define COLOR28		0x1B8		//	W	*	*	*	Color table 28
#define COLOR29		0x1BA		//	W	*	*	*	Color table 29
#define COLOR30		0x1BC		//	W	*	*	*	Color table 30
#define COLOR31		0x1BE		//	W	*	*	*	Color table 31
#define HTOTAL		0x1C0		//	W		*	*	Highest number count, horiz line (VARBEAMEN=1)
#define HSSTOP		0x1C2		//	W		*	*	Horizontal line position for HSYNC stop
#define HBSTRT		0x1C4		//	W		*	*	Horizontal line position for HBLANK start
#define HBSTOP		0x1C6		//	W		*	*	Horizontal line position for HBLANK stop
#define VTOTAL		0x1C8		//	W		*	*	Highest numbered vertical line (VARBEAMEN=1)
#define VSSTOP		0x1CA		//	W		*	*	Vertical line position for VSYNC stop
#define VBSTRT		0x1CC		//	W		*	*	Vertical line for VBLANK start
#define VBSTOP		0x1CE		//	W		*	*	Vertical line for VBLANK stop
#define SPRHSTRT	0x1D0		//	W		*	*	UHRES sprite vertical start
#define SPRHSTOP	0x1D2		//	W		*	*	UHRES sprite vertical stop
#define BPLHSTRT	0x1D4		//	W		*	*	UHRES bit plane vertical start
#define BPLHSTOP	0x1D6		//	W		*	*	UHRES bit plane vertical stop
#define HHPOSW		0x1D8		//	W		*	*	DUAL mode hires H beam counter write
#define HHPOSR		0x1DA		//	R		*	*	DUAL mode hires H beam counter read
#define BEAMCON0	0x1DC		//	W	*	*	*	Beam counter control register (SHRES,UHRES,PAL)
#define HSSTRT		0x1DE		//	W		*	*	Horizontal sync start (VARHSY)
#define VSSTRT		0x1E0		//	W		*	*	Vertical sync start (VARVSY)
#define HCENTER		0x1E2		//	W		*	*	Horizontal position for Vsync on interlace
#define DIWHIGH		0x1E4		//	W		*	*	Display window - upper bits for start/stop
#define BPLHMOD		0x1E6		//	W		*	*	UHRES bit plane modulo
#define SPRHPTH		0x1E8		//	W		*	*	UHRES sprite pointer (high 5 bits)
#define SPRHPTL		0x1EA		//	W		*	*	UHRES sprite pointer (low 15 bits)
#define BPLHPTH		0x1EC		//	W		*	*	VRam (UHRES) bitplane pointer (hi 5 bits)
#define BPLHPTL		0x1EE		//	W		*	*	VRam (UHRES) bitplane pointer (lo 15 bits)
#define FMODE		0x1FC		//	W			*	Fetch mode register