#include "global.h"

// @ 0x08042c3c
__attribute__((naked))
void sub_08042C3C(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r3, r0, #0x0\n"
        "ldr r2, _08042C5C @ =0x0809094C\n"
        "ldr r0, [r2, #0x00]\n"
        "movs r1, #0x01\n"
        "negs r1, r1\n"
        "cmp r0, r1\n"
        "beq _08042C6A\n"
        "adds r4, r1, #0x0\n"
        "adds r1, r2, #0x0\n"
        "_08042C50:\n"
        "ldr r0, [r2, #0x00]\n"
        "cmp r0, r3\n"
        "bne _08042C60\n"
        "ldr r0, [r1, #0x04]\n"
        "b _08042C6E\n"
        ".byte 0x00, 0x00\n"
        "_08042C5C: .4byte 0x0809094C\n"
        "_08042C60:\n"
        "adds r1, #0x08\n"
        "adds r2, #0x08\n"
        "ldr r0, [r1, #0x00]\n"
        "cmp r0, r4\n"
        "bne _08042C50\n"
        "_08042C6A:\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "_08042C6E:\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

