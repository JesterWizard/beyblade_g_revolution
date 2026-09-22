#include "global.h"

// @ 0x080674b4
/* BIOS VBlankIntrWait (SWI 0x05).
 *
 * Every one of the 38 call sites calls this with no arguments, so the parameter
 * list is an empty one.  The AGB BIOS ABI reserves r0-r3 for SWI inputs and
 * results, so a wrapper declares them clobbered; that also leaves r2 as the only
 * free register, which is exactly where the original toolchain materialised the
 * zero (`movs r2, #0`) before `swi 5`. */
void VBlankIntrWait(void)
{
    asm("swi 5" : : "r"(0) : "r0", "r1");
}
