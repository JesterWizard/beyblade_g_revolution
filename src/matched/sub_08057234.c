#include "global.h"

// @ 0x08057234
__attribute__((naked))
void sub_08057234(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "adds r6, r0, #0x0\n"
        "bl sub_0806BE08\n"
        "adds r4, r0, #0x0\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "cmp r4, r0\n"
        "beq _0805726C\n"
        "adds r0, r6, #0x0\n"
        "adds r1, r4, #0x0\n"
        "bl sub_0806BDA8\n"
        "adds r5, r0, #0x0\n"
        "cmp r5, #0x00\n"
        "beq _0805726C\n"
        "movs r4, #0x00\n"
        "b _0805725E\n"
        "_08057258:\n"
        "adds r4, #0x01\n"
        "bl sub_08056D68\n"
        "_0805725E:\n"
        "adds r0, r6, #0x0\n"
        "adds r1, r5, #0x0\n"
        "adds r2, r4, #0x0\n"
        "bl sub_0806BE20\n"
        "cmp r0, #0x00\n"
        "bne _08057258\n"
        "_0805726C:\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

