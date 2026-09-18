#include "global.h"

// @ 0x0806d748
__attribute__((naked))
u8 sub_0806D748(struct Unk6D748 *a, void *b, u32 c, u32 d)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "adds r5, r0, #0x0\n"
        "adds r6, r1, #0x0\n"
        "lsls r3, r3, #0x10\n"
        "lsrs r3, r3, #0x10\n"
        "movs r1, #0x01\n"
        "adds r0, #0x94\n"
        "ldr r0, [r0, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _0806D76E\n"
        "ldr r4, [r0, #0x08]\n"
        "cmp r4, #0x00\n"
        "beq _0806D76E\n"
        "adds r0, r5, #0x0\n"
        "adds r1, r6, #0x0\n"
        "bl _08073C50\n"
        "lsls r0, r0, #0x18\n"
        "lsrs r1, r0, #0x18\n"
        "_0806D76E:\n"
        "adds r0, r1, #0x0\n"
        "pop {r4, r5, r6}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

