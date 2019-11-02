#pragma once

#pragma GCC diagnostic ignored "-Wstrict-aliasing"

/* Helpers */
#define GETBYTE_HI(var) (*(volatile UBYTE*)&var)
#define GETBYTE_LO(var) (*((volatile UBYTE*)&var+1))
#define GETWORD(var) (*(volatile UWORD*)&var)
#define GETLONG(var) (*(volatile ULONG*)&var)

/* Copperlist helpers */
#define CMOVE(addr, data) addr, data
#define CWAIT(vhpos, flags) vhpos, flags
#define CEND 0xffff, 0xfffe
