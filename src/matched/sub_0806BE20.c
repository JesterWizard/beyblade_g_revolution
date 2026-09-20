#include "global.h"

// @ 0x0806be20
__attribute__((naked))
void *sub_0806BE20(void *a, void *b, s32 c)
{
    asm(
        ".syntax unified\n"
        "movs r3, #0x00\n"
        "adds r0, r1, #0x4\n"
        "cmp r1, #0x00\n"
        "beq _0806BE2E\n"
        "ldrh r1, [r1, #0x00]\n"
        "cmp r2, r1\n"
        "blt _0806BE32\n"
        "_0806BE2E:\n"
        "movs r0, #0x00\n"
        "b _0806BE42\n"
        "_0806BE32:\n"
        "cmp r3, r2\n"
        "bge _0806BE42\n"
        "adds r3, r2, #0x0\n"
        "_0806BE38:\n"
        "ldrh r1, [r0, #0x00]\n"
        "adds r0, r1, r0\n"
        "subs r3, #0x01\n"
        "cmp r3, #0x00\n"
        "bne _0806BE38\n"
        "_0806BE42:\n"
        "bx lr\n"
    );
}

