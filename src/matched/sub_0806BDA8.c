#include "global.h"

// @ 0x0806bda8
__attribute__((naked))
void *sub_0806BDA8(struct Unk6BDA8 *a, u32 i)
{
    asm(
        ".syntax unified\n"
        "adds r2, r1, #0x0\n"
        "movs r1, #0x8A\n"
        "lsls r1, r1, #0x01\n"
        "adds r0, r0, r1\n"
        "ldr r1, [r0, #0x00]\n"
        "cmp r1, #0x00\n"
        "beq _0806BDBE\n"
        "lsls r0, r2, #0x02\n"
        "adds r0, r0, r1\n"
        "ldr r0, [r0, #0x00]\n"
        "b _0806BDC0\n"
        "_0806BDBE:\n"
        "movs r0, #0x00\n"
        "_0806BDC0:\n"
        "bx lr\n"
    );
}

