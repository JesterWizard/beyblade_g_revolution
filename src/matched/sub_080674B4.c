#include "global.h"

// @ 0x080674b4
/* BIOS VBlankIntrWait (SWI 0x05). Called with no arguments at every one of its
 * 38 call sites; the emitted `movs r2, #0` is the original toolchain's inline
 * form and is reproduced here. The previous signature claimed two pointer
 * parameters, which no caller has ever passed. */
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
