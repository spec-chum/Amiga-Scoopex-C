# Amiga-Scoopex-C

My attempt at converting Scoopex's superb Amiga Hardware coding tutorials into C.

Tutorial playlist: https://www.youtube.com/playlist?list=PLc3ltHgmiidpK-s0eP5hTKJnjdTHz0_bW

The toolchain I use is this one: https://github.com/BartmanAbyss/vscode-amiga-debug which has great debugging via VSCode.

Once his extension is installed, as per the simple instructions on his repo, you *should* be able to just open the folder in VSCode and press F5 to run.  *Should.*

## PLEASE NOTE

***When doing tutorial 9 - "DMA control and sprites" I noticed a problem with using `-Ofast` in the makefile, in that it would put some code from inside of a loop to the outside, obviously breaking the code.  I had previously assumed it to be an issue with "\_\_attribute\_\_((section("tut.MEMF_CHIP")))" making the section read-only.***

***I've fixed this in tutorial 9 but decided not to "backport" the fix to previous tutorials, as they only had 1 array (copperlist) that needed to be in Chipmem and already had a workaround (CopyMem to allocated Chipmem), but to remedy the issue, if you're following along, please edit all Makefile8mingw makefiles after tutorial 8 to say `-O1` on the `CCFLAGS` line.***
