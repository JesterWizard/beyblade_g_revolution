#include "global.h"

// @ 0x080361a8
__attribute__((naked))
void sub_080361A8(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "movs r3, #0x0C\n"
        "ldr r4, _080361C8 @ =0x0000FFFF\n"
        "ldrh r1, [r0, #0x1C]\n"
        "str r1, [r0, #0x1C]\n"
        "ldr r2, [r0, #0x14]\n"
        "subs r1, r1, r2\n"
        "muls r1, r3\n"
        "asrs r1, r1, #0x08\n"
        "str r1, [r0, #0x18]\n"
        "adds r2, r2, r1\n"
        "ands r2, r4\n"
        "str r2, [r0, #0x14]\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_080361C8: .4byte 0x0000FFFF\n"
    );
}

