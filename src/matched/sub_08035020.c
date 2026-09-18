#include "global.h"

// @ 0x08035020
__attribute__((naked))
void sub_08035020(struct Unk346C0 *a, u32 b)
{
    asm(
        ".syntax unified\n"
        "adds r2, r0, #0x0\n"
        "movs r0, #0xB3\n"
        "lsls r0, r0, #0x02\n"
        "adds r3, r2, r0\n"
        "ldr r0, [r3, #0x00]\n"
        "cmp r0, #0x02\n"
        "blt _08035036\n"
        "cmp r0, #0x03\n"
        "ble _08035052\n"
        "cmp r0, #0x06\n"
        "beq _08035052\n"
        "_08035036:\n"
        "cmp r0, #0x07\n"
        "beq _08035046\n"
        "movs r0, #0x07\n"
        "str r0, [r3, #0x00]\n"
        "movs r3, #0xBF\n"
        "lsls r3, r3, #0x02\n"
        "adds r0, r2, r3\n"
        "str r1, [r0, #0x00]\n"
        "_08035046:\n"
        "movs r0, #0xBE\n"
        "lsls r0, r0, #0x02\n"
        "adds r1, r2, r0\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "str r0, [r1, #0x00]\n"
        "_08035052:\n"
        "bx lr\n"
    );
}

