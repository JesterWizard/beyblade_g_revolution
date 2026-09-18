#include "global.h"

// @ 0x0806f1a0
__attribute__((naked))
void sub_0806F1A0(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r4, r0, #0x0\n"
        "lsls r1, r1, #0x10\n"
        "lsrs r1, r1, #0x10\n"
        "movs r3, #0x00\n"
        "lsls r2, r2, #0x10\n"
        "asrs r2, r2, #0x10\n"
        "cmp r3, r2\n"
        "bge _0806F1D0\n"
        "_0806F1B2:\n"
        "ldr r0, [r4, #0x00]\n"
        "cmp r1, r0\n"
        "bne _0806F1BE\n"
        "lsls r0, r3, #0x10\n"
        "asrs r0, r0, #0x10\n"
        "b _0806F1D4\n"
        "_0806F1BE:\n"
        "adds r4, #0x84\n"
        "lsls r0, r3, #0x10\n"
        "movs r3, #0x80\n"
        "lsls r3, r3, #0x09\n"
        "adds r0, r0, r3\n"
        "lsrs r3, r0, #0x10\n"
        "asrs r0, r0, #0x10\n"
        "cmp r0, r2\n"
        "blt _0806F1B2\n"
        "_0806F1D0:\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "_0806F1D4:\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

