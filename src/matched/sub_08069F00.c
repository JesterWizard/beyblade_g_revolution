#include "global.h"

// @ 0x08069f00
__attribute__((naked))
s32 sub_08069F00(s16 a, s16 b)
{
    asm(
        ".syntax unified\n"
        "lsls r0, r0, #0x10\n"
        "asrs r0, r0, #0x10\n"
        "lsls r1, r1, #0x10\n"
        "asrs r1, r1, #0x10\n"
        "muls r0, r1\n"
        "adds r1, r0, #0x0\n"
        "cmp r0, #0x00\n"
        "bge _08069F12\n"
        "adds r1, #0xFF\n"
        "_08069F12:\n"
        "lsls r0, r1, #0x08\n"
        "asrs r0, r0, #0x10\n"
        "bx lr\n"
    );
}

