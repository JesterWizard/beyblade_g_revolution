#include "global.h"

// @ 0x08061dc0
__attribute__((naked))
void sub_08061DC0(u16 a, u16 b)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r3, r1, #0x0\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r0, r0, #0x10\n"
        "lsls r3, r3, #0x10\n"
        "lsrs r3, r3, #0x10\n"
        "ldr r1, _08061E00 @ =0x03000798\n"
        "ldr r1, [r1, #0x00]\n"
        "adds r2, r1, #0x0\n"
        "adds r2, #0x98\n"
        "ldrh r2, [r2, #0x00]\n"
        "lsrs r2, r2, #0x03\n"
        "lsls r2, r2, #0x05\n"
        "adds r1, #0x5D\n"
        "ldrb r1, [r1, #0x00]\n"
        "lsls r1, r1, #0x0E\n"
        "muls r0, r2\n"
        "movs r4, #0xC0\n"
        "lsls r4, r4, #0x13\n"
        "adds r0, r0, r4\n"
        "adds r0, r1, r0\n"
        "muls r3, r2\n"
        "adds r3, r3, r4\n"
        "adds r1, r1, r3\n"
        "ldr r3, _08061E04 @ =0x080BB8C0\n"
        "ldr r3, [r3, #0x00]\n"
        "bl _08073C4C\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08061E00: .4byte 0x03000798\n"
        "_08061E04: .4byte 0x080BB8C0\n"
    );
}

