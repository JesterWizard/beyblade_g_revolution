#include "global.h"

// @ 0x0806def4
__attribute__((naked))
s32 sub_0806DEF4(struct Unk6DEF4 *a, s32 b)
{
    asm(
        ".syntax unified\n"
        "ldr r2, [r0, #0x04]\n"
        "ldr r0, [r0, #0x00]\n"
        "ldr r0, [r0, #0x00]\n"
        "cmp r1, r0\n"
        "blt _0806DF02\n"
        "movs r0, #0x00\n"
        "b _0806DF06\n"
        "_0806DF02:\n"
        "lsls r0, r1, #0x04\n"
        "adds r0, r2, r0\n"
        "_0806DF06:\n"
        "bx lr\n"
    );
}

