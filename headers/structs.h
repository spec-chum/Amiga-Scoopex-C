#pragma once

/*  Need to include this yourself if not including this file
    as it's needed by GCC8  */
struct ExecBase *SysBase;

/* Common structs */
volatile struct Custom *custom = (struct Custom *)0xdff000;
volatile struct CIA *ciaa = (struct CIA *)0xbfe001;
