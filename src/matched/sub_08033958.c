#include "global.h"

// @ 0x08033958
__attribute__((naked))
s32 sub_08033958(struct Unk33958 *a)
{
    asm(
        ".syntax unified\n"
        "movs r2, #0x00\n"
        "movs r3, #0x00\n"
        "ldsh r1, [r0, r3]\n"
        "ldr r0, [r0, #0x04]\n"
        "ldr r0, [r0, #0x00]\n"
        "cmp r1, r0\n"
        "bne _08033968\n"
        "movs r2, #0x01\n"
        "_08033968:\n"
        "adds r0, r2, #0x0\n"
        "bx lr\n"
    );
}

