#include "global.h"

// @ 0x08042bb0
__attribute__((naked))
s32 sub_08042BB0(s32 a)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r3, r0, #0x0\n"
        "ldr r2, _08042BD0 @ =0x080908BC\n"
        "ldr r0, [r2, #0x00]\n"
        "movs r1, #0x01\n"
        "negs r1, r1\n"
        "cmp r0, r1\n"
        "beq _08042BDE\n"
        "adds r4, r1, #0x0\n"
        "adds r1, r2, #0x0\n"
        "_08042BC4:\n"
        "ldr r0, [r2, #0x00]\n"
        "cmp r0, r3\n"
        "bne _08042BD4\n"
        "ldr r0, [r1, #0x04]\n"
        "b _08042BE2\n"
        ".byte 0x00, 0x00\n"
        "_08042BD0: .4byte 0x080908BC\n"
        "_08042BD4:\n"
        "adds r1, #0x08\n"
        "adds r2, #0x08\n"
        "ldr r0, [r1, #0x00]\n"
        "cmp r0, r4\n"
        "bne _08042BC4\n"
        "_08042BDE:\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "_08042BE2:\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

