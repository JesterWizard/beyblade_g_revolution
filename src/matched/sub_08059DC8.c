#include "global.h"

// @ 0x08059dc8
__attribute__((naked))
void sub_08059DC8(u32 a)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "add sp, #-0x00C\n"
        "adds r2, r0, #0x0\n"
        "movs r0, #0x01\n"
        "str r0, [sp, #0x000]\n"
        "movs r0, #0x00\n"
        "str r0, [sp, #0x008]\n"
        "str r0, [sp, #0x004]\n"
        "cmp r1, #0x00\n"
        "beq _08059DFE\n"
        "ldr r0, _08059E08 @ =0x03000734\n"
        "str r2, [r0, #0x00]\n"
        "ldr r5, _08059E0C @ =0x08099710\n"
        "_08059DE2:\n"
        "ldr r0, [r1, #0x00]\n"
        "lsls r0, r0, #0x02\n"
        "adds r0, r0, r5\n"
        "ldr r4, [r0, #0x00]\n"
        "adds r0, r1, #0x0\n"
        "mov r1, sp\n"
        "add r2, sp, #0x004\n"
        "add r3, sp, #0x008\n"
        "bl _08073C50\n"
        "adds r1, r0, #0x0\n"
        "ldr r0, [sp, #0x008]\n"
        "cmp r0, #0x00\n"
        "beq _08059DE2\n"
        "_08059DFE:\n"
        "add sp, #0x00C\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08059E08: .4byte 0x03000734\n"
        "_08059E0C: .4byte 0x08099710\n"
    );
}

