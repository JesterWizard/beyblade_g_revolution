#include "global.h"

// @ 0x08060d28
__attribute__((naked))
void sub_08060D28(struct Unk0798 *a)
{
    asm(
        ".syntax unified\n"
        "push {lr}\n"
        "adds r2, r0, #0x0\n"
        "cmp r2, #0x00\n"
        "beq _08060D4E\n"
        "ldr r3, _08060D54 @ =0x080BB8BC\n"
        "adds r0, #0x5D\n"
        "ldrb r0, [r0, #0x00]\n"
        "lsls r1, r0, #0x0E\n"
        "movs r0, #0xC0\n"
        "lsls r0, r0, #0x13\n"
        "adds r1, r1, r0\n"
        "adds r0, r2, #0x0\n"
        "adds r0, #0x94\n"
        "ldrh r0, [r0, #0x00]\n"
        "lsls r2, r0, #0x05\n"
        "ldr r3, [r3, #0x00]\n"
        "movs r0, #0x00\n"
        "bl _08073C4C\n"
        "_08060D4E:\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08060D54: .4byte 0x080BB8BC\n"
    );
}

