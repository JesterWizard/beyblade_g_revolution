#include "global.h"

// @ 0x08061308
__attribute__((naked))
void sub_08061308(void)
{
    asm(
        ".syntax unified\n"
        "push {lr}\n"
        "ldr r3, _08061330 @ =0x080BB8BC\n"
        "ldr r0, _08061334 @ =0x03000798\n"
        "ldr r2, [r0, #0x00]\n"
        "adds r0, r2, #0x0\n"
        "adds r0, #0x5D\n"
        "ldrb r0, [r0, #0x00]\n"
        "lsls r1, r0, #0x0E\n"
        "movs r0, #0xC0\n"
        "lsls r0, r0, #0x13\n"
        "adds r1, r1, r0\n"
        "adds r2, #0x94\n"
        "ldrh r2, [r2, #0x00]\n"
        "lsls r2, r2, #0x05\n"
        "ldr r3, [r3, #0x00]\n"
        "movs r0, #0x00\n"
        "bl _08073C4C\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08061330: .4byte 0x080BB8BC\n"
        "_08061334: .4byte 0x03000798\n"
    );
}

