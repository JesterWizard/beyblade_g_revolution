#include "global.h"

// @ 0x080726e0
__attribute__((naked))
void sub_080726E0(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "adds r4, r0, #0x0\n"
        "adds r5, r1, #0x0\n"
        "adds r1, r2, #0x0\n"
        "movs r2, #0x08\n"
        "ldsh r0, [r4, r2]\n"
        "cmp r1, r0\n"
        "bge _0807270A\n"
        "ldr r3, _08072710 @ =0x080BB8C0\n"
        "ldrh r2, [r4, #0x06]\n"
        "muls r1, r2\n"
        "lsls r1, r1, #0x01\n"
        "ldr r0, [r4, #0x0C]\n"
        "adds r0, r0, r1\n"
        "ldrh r4, [r4, #0x04]\n"
        "lsls r1, r4, #0x01\n"
        "adds r1, r5, r1\n"
        "lsls r2, r2, #0x01\n"
        "ldr r3, [r3, #0x00]\n"
        "bl _08073C4C\n"
        "_0807270A:\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08072710: .4byte 0x080BB8C0\n"
    );
}

