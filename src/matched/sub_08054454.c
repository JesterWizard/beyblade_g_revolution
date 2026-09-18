#include "global.h"

// @ 0x08054454
__attribute__((naked))
void sub_08054454(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "ldr r1, _08054490 @ =0x0300070C\n"
        "ldr r0, [r1, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _0805448A\n"
        "movs r5, #0x00\n"
        "adds r6, r1, #0x0\n"
        "_08054462:\n"
        "ldr r0, [r6, #0x00]\n"
        "lsls r4, r5, #0x02\n"
        "adds r0, r0, r4\n"
        "ldr r0, [r0, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _0805447A\n"
        "bl sub_0806FE84\n"
        "ldr r0, [r6, #0x00]\n"
        "adds r0, r0, r4\n"
        "movs r1, #0x00\n"
        "str r1, [r0, #0x00]\n"
        "_0805447A:\n"
        "adds r5, #0x01\n"
        "cmp r5, #0x0C\n"
        "ble _08054462\n"
        "ldr r0, _08054490 @ =0x0300070C\n"
        "ldr r0, [r0, #0x00]\n"
        "adds r0, #0x34\n"
        "bl sub_08070678\n"
        "_0805448A:\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08054490: .4byte 0x0300070C\n"
    );
}

