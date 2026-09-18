#include "global.h"

// @ 0x0806c78c
__attribute__((naked))
void sub_0806C78C(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "add sp, #-0x018\n"
        "adds r4, r0, #0x0\n"
        "adds r5, r1, #0x0\n"
        "str r2, [sp, #0x000]\n"
        "add r1, sp, #0x004\n"
        "movs r2, #0x00\n"
        "movs r3, #0x01\n"
        "bl sub_0806DF38\n"
        "lsls r0, r0, #0x10\n"
        "cmp r0, #0x00\n"
        "beq _0806C7CA\n"
        "ldr r0, [sp, #0x004]\n"
        "ldr r0, [r0, #0x00]\n"
        "cmp r0, #0x01\n"
        "bgt _0806C7B2\n"
        "movs r0, #0x00\n"
        "b _0806C7CA\n"
        "_0806C7B2:\n"
        "ldr r1, [sp, #0x008]\n"
        "lsls r3, r1, #0x0A\n"
        "subs r0, #0x01\n"
        "cmp r1, r0\n"
        "bne _0806C7BE\n"
        "subs r3, #0x10\n"
        "_0806C7BE:\n"
        "ldr r2, [sp, #0x00C]\n"
        "adds r0, r4, #0x0\n"
        "adds r1, r5, #0x0\n"
        "bl sub_0806C704\n"
        "movs r0, #0x01\n"
        "_0806C7CA:\n"
        "add sp, #0x018\n"
        "pop {r4, r5}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

