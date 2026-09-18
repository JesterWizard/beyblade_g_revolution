#include "global.h"

// @ 0x0806fdb4
__attribute__((naked))
struct Unk6FDB4 *sub_0806FDB4(struct Unk6FDB4 *p, u16 key)
{
    asm(
        ".syntax unified\n"
        "lsls r1, r1, #0x10\n"
        "lsrs r1, r1, #0x10\n"
        "movs r2, #0x00\n"
        "cmp r0, #0x00\n"
        "beq _0806FDCC\n"
        "_0806FDBE:\n"
        "ldrh r3, [r0, #0x22]\n"
        "cmp r3, r1\n"
        "bcs _0806FDCC\n"
        "adds r2, r0, #0x0\n"
        "ldr r0, [r2, #0x04]\n"
        "cmp r0, #0x00\n"
        "bne _0806FDBE\n"
        "_0806FDCC:\n"
        "adds r0, r2, #0x0\n"
        "bx lr\n"
    );
}

