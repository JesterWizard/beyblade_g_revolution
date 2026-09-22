#include "global.h"

// @ 0x080674b4
/* BIOS VBlankIntrWait (SWI 0x05), called with no arguments at all 38 call sites.
 * Superseded: this function now byte-matches in src/matched/sub_080674B4.c, so
 * this file is kept only as the draft record. */
__attribute__((naked))
void VBlankIntrWait(void)
{
    asm(
        ".syntax unified\n"
        "movs r2, #0\n"
        "swi #5\n"
        "bx lr\n"
    );
}
