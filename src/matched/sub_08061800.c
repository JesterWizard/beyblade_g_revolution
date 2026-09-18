#include "global.h"

// @ 0x08061800
__attribute__((naked))
void sub_08061800(u16 a)
{
    asm(
        ".syntax unified\n"
        "push {lr}\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r3, r0, #0x10\n"
        "ldr r0, _08061844 @ =0x03000798\n"
        "ldr r2, [r0, #0x00]\n"
        "adds r0, r2, #0x0\n"
        "adds r0, #0x9A\n"
        "ldrh r0, [r0, #0x00]\n"
        "lsrs r0, r0, #0x03\n"
        "subs r0, #0x01\n"
        "cmp r3, r0\n"
        "bge _08061840\n"
        "adds r0, r2, #0x0\n"
        "adds r0, #0x5D\n"
        "ldrb r0, [r0, #0x00]\n"
        "lsls r1, r0, #0x0E\n"
        "adds r0, r2, #0x0\n"
        "adds r0, #0x98\n"
        "ldrh r0, [r0, #0x00]\n"
        "lsrs r2, r0, #0x03\n"
        "lsls r2, r2, #0x05\n"
        "adds r0, r3, #0x0\n"
        "muls r0, r2\n"
        "movs r3, #0xC0\n"
        "lsls r3, r3, #0x13\n"
        "adds r0, r0, r3\n"
        "adds r1, r1, r0\n"
        "ldr r0, _08061848 @ =0x080BB8BC\n"
        "ldr r3, [r0, #0x00]\n"
        "movs r0, #0x00\n"
        "bl _08073C4C\n"
        "_08061840:\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08061844: .4byte 0x03000798\n"
        "_08061848: .4byte 0x080BB8BC\n"
    );
}

