#include "global.h"

// @ 0x08062634
__attribute__((naked))
void sub_08062634(struct Unk62634 *a, u32 b, u32 c, u32 d)
{
    asm(
        ".syntax unified\n"
        "cmp r0, #0x00\n"
        "beq _0806263E\n"
        "str r1, [r0, #0x1C]\n"
        "str r2, [r0, #0x20]\n"
        "str r3, [r0, #0x18]\n"
        "_0806263E:\n"
        "bx lr\n"
    );
}

