#include "global.h"

// @ 0x08033f30
__attribute__((naked))
void sub_08033F30(struct Unk33F30 *a, s32 b)
{
    asm(
        ".syntax unified\n"
        "adds r2, r0, #0x0\n"
        "str r1, [r2, #0x14]\n"
        "movs r0, #0x01\n"
        "strb r0, [r2, #0x1C]\n"
        "cmp r1, #0x00\n"
        "blt _08033F40\n"
        "movs r0, #0x00\n"
        "b _08033F44\n"
        "_08033F40:\n"
        "movs r0, #0x80\n"
        "lsls r0, r0, #0x04\n"
        "_08033F44:\n"
        "str r0, [r2, #0x18]\n"
        "bx lr\n"
    );
}

