#include "global.h"

// @ 0x08040088
__attribute__((naked))
void sub_08040088(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "movs r2, #0x9D\n"
        "lsls r2, r2, #0x02\n"
        "adds r1, r0, r2\n"
        "ldr r3, [r1, #0x00]\n"
        "cmp r3, #0x00\n"
        "beq _080400BA\n"
        "movs r4, #0xC1\n"
        "lsls r4, r4, #0x02\n"
        "adds r2, r0, r4\n"
        "ldr r0, [r2, #0x00]\n"
        "subs r0, #0x01\n"
        "str r0, [r2, #0x00]\n"
        "cmp r0, #0x00\n"
        "bne _080400BA\n"
        "movs r0, #0x04\n"
        "str r0, [r2, #0x00]\n"
        "ldrh r0, [r3, #0x18]\n"
        "adds r0, #0x01\n"
        "strh r0, [r3, #0x18]\n"
        "ldr r1, [r1, #0x00]\n"
        "movs r0, #0x03\n"
        "ldrh r2, [r1, #0x18]\n"
        "ands r0, r2\n"
        "strh r0, [r1, #0x18]\n"
        "_080400BA:\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

