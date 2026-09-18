#include "global.h"

// @ 0x080347e4
__attribute__((naked))
void sub_080347E4(struct Unk346C0 *a)
{
    asm(
        ".syntax unified\n"
        "adds r1, r0, #0x0\n"
        "ldr r2, [r1, #0x00]\n"
        "cmp r2, #0x00\n"
        "beq _0803480E\n"
        "movs r3, #0xB7\n"
        "lsls r3, r3, #0x02\n"
        "adds r0, r1, r3\n"
        "ldr r0, [r0, #0x00]\n"
        "str r0, [r2, #0x30]\n"
        "subs r3, #0x04\n"
        "adds r0, r1, r3\n"
        "ldr r0, [r0, #0x00]\n"
        "str r0, [r2, #0x4C]\n"
        "subs r3, #0x04\n"
        "adds r0, r1, r3\n"
        "ldr r0, [r0, #0x00]\n"
        "str r0, [r2, #0x48]\n"
        "adds r3, #0x0C\n"
        "adds r0, r1, r3\n"
        "ldr r0, [r0, #0x00]\n"
        "str r0, [r2, #0x34]\n"
        "_0803480E:\n"
        "bx lr\n"
    );
}

