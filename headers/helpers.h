/*	Helpers */
#define HIBYTE(theword) (theword >> 8)
#define LOBYTE(theword) (theword & 0xff)

/* Copperlist helpers */
#define CMOVE(addr, data) addr, data
#define CWAIT(vhpos, flags) vhpos, flags
#define CEND 0xffff, 0xfffe