#include "global.h"

// @ 0x08066ad4
__attribute__((naked))
void sub_08066AD4(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r3, r0, #0x0\n"
        "movs r0, #0xA3\n"
        "lsls r0, r0, #0x02\n"
        "adds r1, r3, r0\n"
        "ldr r2, [r1, #0x00]\n"
        "movs r4, #0xC1\n"
        "lsls r4, r4, #0x02\n"
        "adds r0, r3, r4\n"
        "ldr r0, [r0, #0x00]\n"
        "lsls r0, r0, #0x0C\n"
        "movs r4, #0x80\n"
        "lsls r4, r4, #0x06\n"
        "adds r0, r0, r4\n"
        "str r0, [r2, #0x08]\n"
        "ldr r2, [r1, #0x00]\n"
        "movs r1, #0xC2\n"
        "lsls r1, r1, #0x02\n"
        "adds r0, r3, r1\n"
        "ldr r1, [r0, #0x00]\n"
        "lsls r0, r1, #0x02\n"
        "adds r0, r0, r1\n"
        "lsls r0, r0, #0x0A\n"
        "movs r4, #0xB0\n"
        "lsls r4, r4, #0x06\n"
        "adds r0, r0, r4\n"
        "str r0, [r2, #0x0C]\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

