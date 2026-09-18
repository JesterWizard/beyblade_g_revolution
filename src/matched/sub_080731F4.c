#include "global.h"

// @ 0x080731f4
__attribute__((naked))
s32 sub_080731F4(u8 *s)
{
    asm(
        ".syntax unified\n"
        "adds r1, r0, #0x0\n"
        "movs r2, #0x00\n"
        "cmp r1, #0x00\n"
        "bne _08073200\n"
        "movs r0, #0x00\n"
        "b _08073216\n"
        "_08073200:\n"
        "ldrb r0, [r1, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _08073214\n"
        "movs r3, #0x00\n"
        "_08073208:\n"
        "strb r3, [r1, #0x00]\n"
        "adds r1, #0x01\n"
        "adds r2, #0x01\n"
        "ldrb r0, [r1, #0x00]\n"
        "cmp r0, #0x00\n"
        "bne _08073208\n"
        "_08073214:\n"
        "adds r0, r2, #0x0\n"
        "_08073216:\n"
        "bx lr\n"
    );
}

