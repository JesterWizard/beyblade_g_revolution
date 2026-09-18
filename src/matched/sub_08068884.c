#include "global.h"

// @ 0x08068884
__attribute__((naked))
void *sub_08068884(struct Unk68014 *a)
{
    asm(
        ".syntax unified\n"
        "ldr r1, [r0, #0x08]\n"
        "lsls r1, r1, #0x03\n"
        "adds r1, #0x20\n"
        "adds r2, r0, r1\n"
        "ldr r1, [r0, #0x18]\n"
        "adds r0, r0, r1\n"
        "cmp r2, r0\n"
        "beq _08068898\n"
        "adds r0, r2, #0x0\n"
        "b _0806889A\n"
        "_08068898:\n"
        "movs r0, #0x00\n"
        "_0806889A:\n"
        "bx lr\n"
    );
}

