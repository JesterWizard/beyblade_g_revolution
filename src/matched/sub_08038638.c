#include "global.h"

// @ 0x08038638
__attribute__((naked))
void sub_08038638(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r0, r0, #0x10\n"
        "adds r1, r0, #0x0\n"
        "ldr r5, _08038674 @ =0x030003CC\n"
        "ldr r0, [r5, #0x00]\n"
        "lsls r4, r1, #0x01\n"
        "adds r0, #0x22\n"
        "adds r2, r0, r4\n"
        "ldrh r3, [r2, #0x00]\n"
        "movs r6, #0x00\n"
        "ldsh r0, [r2, r6]\n"
        "cmp r0, #0x00\n"
        "ble _08038658\n"
        "subs r0, r3, #0x1\n"
        "strh r0, [r2, #0x00]\n"
        "_08038658:\n"
        "ldr r0, [r5, #0x00]\n"
        "adds r0, #0x22\n"
        "adds r0, r0, r4\n"
        "movs r2, #0x00\n"
        "ldsh r0, [r0, r2]\n"
        "cmp r0, #0x00\n"
        "bne _0803866C\n"
        "adds r0, r1, #0x0\n"
        "bl sub_080385DC\n"
        "_0803866C:\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08038674: .4byte 0x030003CC\n"
    );
}

