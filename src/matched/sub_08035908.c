#include "global.h"

// @ 0x08035908
__attribute__((naked))
u8 sub_08035908(struct Unk35878 *a)
{
    asm(
        ".syntax unified\n"
        "ldr r2, [r0, #0x04]\n"
        "ldr r3, [r0, #0x00]\n"
        "cmp r2, #0x00\n"
        "beq _08035928\n"
        "b _08035922\n"
        "_08035912:\n"
        "ldr r0, [r2, #0x00]\n"
        "ldr r1, [r2, #0x04]\n"
        "adds r0, r0, r1\n"
        "cmp r3, r0\n"
        "bgt _08035920\n"
        "movs r0, #0x00\n"
        "b _0803592A\n"
        "_08035920:\n"
        "adds r2, #0x10\n"
        "_08035922:\n"
        "ldr r0, [r2, #0x08]\n"
        "cmp r0, #0x00\n"
        "bne _08035912\n"
        "_08035928:\n"
        "movs r0, #0x01\n"
        "_0803592A:\n"
        "bx lr\n"
    );
}

