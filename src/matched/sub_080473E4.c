#include "global.h"

// @ 0x080473e4
__attribute__((naked))
void sub_080473E4(void)
{
    asm(
        ".syntax unified\n"
        "ldr r0, _080473F0 @ =0x03000634\n"
        "movs r1, #0x00\n"
        "str r1, [r0, #0x00]\n"
        "ldr r0, _080473F4 @ =0x0300063C\n"
        "str r1, [r0, #0x00]\n"
        "bx lr\n"
        "_080473F0: .4byte 0x03000634\n"
        "_080473F4: .4byte 0x0300063C\n"
    );
}

