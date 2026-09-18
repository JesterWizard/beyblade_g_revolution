#include "global.h"

// @ 0x08073a28
__attribute__((naked))
void sub_08073A28(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, r7, lr}\n"
        "adds r5, r0, #0x0\n"
        "lsls r1, r1, #0x18\n"
        "lsrs r7, r1, #0x18\n"
        "lsls r2, r2, #0x10\n"
        "lsrs r4, r2, #0x10\n"
        "adds r6, r4, #0x0\n"
        "cmp r5, #0x00\n"
        "beq _08073A64\n"
        "cmp r4, #0x00\n"
        "beq _08073A64\n"
        "bl sub_08073078\n"
        "adds r1, r0, #0x0\n"
        "subs r0, r4, #0x1\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r4, r0, #0x10\n"
        "cmp r6, r1\n"
        "bgt _08073A64\n"
        "adds r2, r1, #0x0\n"
        "adds r3, r5, r4\n"
        "cmp r2, r4\n"
        "blt _08073A62\n"
        "_08073A56:\n"
        "adds r1, r2, r5\n"
        "ldrb r0, [r1, #0x00]\n"
        "strb r0, [r1, #0x01]\n"
        "subs r2, #0x01\n"
        "cmp r2, r4\n"
        "bge _08073A56\n"
        "_08073A62:\n"
        "strb r7, [r3, #0x00]\n"
        "_08073A64:\n"
        "pop {r4, r5, r6, r7}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

