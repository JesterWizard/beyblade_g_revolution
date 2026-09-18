#include "global.h"

// @ 0x08062684
__attribute__((naked))
void sub_08062684(struct Unk62634 *a)
{
    asm(
        ".syntax unified\n"
        "adds r2, r0, #0x0\n"
        "cmp r2, #0x00\n"
        "beq _08062696\n"
        "movs r1, #0x00\n"
        "str r1, [r2, #0x18]\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "str r0, [r2, #0x1C]\n"
        "str r1, [r2, #0x20]\n"
        "_08062696:\n"
        "bx lr\n"
    );
}

