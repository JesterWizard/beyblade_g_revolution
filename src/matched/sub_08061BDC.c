#include "global.h"

// @ 0x08061bdc
__attribute__((naked))
void sub_08061BDC(struct Unk61BDC *a)
{
    asm(
        ".syntax unified\n"
        "adds r1, r0, #0x0\n"
        "cmp r1, #0x00\n"
        "beq _08061BE6\n"
        "movs r0, #0x01\n"
        "strb r0, [r1, #0x14]\n"
        "_08061BE6:\n"
        "bx lr\n"
    );
}

