#include "global.h"

// @ 0x08073078
__attribute__((naked))
s32 sub_08073078(u8 *s)
{
    asm(
        ".syntax unified\n"
        "adds r2, r0, #0x0\n"
        "movs r1, #0x00\n"
        "cmp r2, #0x00\n"
        "bne _08073086\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "b _08073098\n"
        "_08073086:\n"
        "ldrb r0, [r2, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _08073096\n"
        "_0807308C:\n"
        "adds r1, #0x01\n"
        "adds r0, r2, r1\n"
        "ldrb r0, [r0, #0x00]\n"
        "cmp r0, #0x00\n"
        "bne _0807308C\n"
        "_08073096:\n"
        "adds r0, r1, #0x0\n"
        "_08073098:\n"
        "bx lr\n"
    );
}

