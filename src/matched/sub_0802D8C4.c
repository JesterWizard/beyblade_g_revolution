#include "global.h"

// @ 0x0802d8c4
__attribute__((naked))
void sub_0802D8C4(s32 a)
{
    asm(
        ".syntax unified\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r1, r0, #0x10\n"
        "ldr r0, _0802D8D8 @ =0x0300026C\n"
        "ldr r0, [r0, #0x00]\n"
        "ldr r0, [r0, #0x08]\n"
        "cmp r0, #0x00\n"
        "beq _0802D8D4\n"
        "strh r1, [r0, #0x18]\n"
        "_0802D8D4:\n"
        "bx lr\n"
        ".byte 0x00, 0x00\n"
        "_0802D8D8: .4byte 0x0300026C\n"
    );
}

