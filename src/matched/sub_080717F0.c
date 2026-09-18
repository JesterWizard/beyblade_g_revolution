#include "global.h"

// @ 0x080717f0
__attribute__((naked))
void sub_080717F0(u32 a)
{
    asm(
        ".syntax unified\n"
        "adds r1, r0, #0x0\n"
        "movs r0, #0x80\n"
        "lsls r0, r0, #0x01\n"
        "cmp r1, r0\n"
        "bls _080717FC\n"
        "adds r1, r0, #0x0\n"
        "_080717FC:\n"
        "ldr r0, _08071804 @ =0x030000CC\n"
        "strh r1, [r0, #0x00]\n"
        "bx lr\n"
        ".byte 0x00, 0x00\n"
        "_08071804: .4byte 0x030000CC\n"
    );
}

