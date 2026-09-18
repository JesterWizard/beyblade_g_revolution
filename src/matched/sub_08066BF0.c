#include "global.h"

// @ 0x08066bf0
__attribute__((naked))
void sub_08066BF0(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "movs r1, #0x8C\n"
        "lsls r1, r1, #0x02\n"
        "adds r0, r0, r1\n"
        "ldr r0, [r0, #0x00]\n"
        "ldr r6, _08066C14 @ =0x030009A8\n"
        "ldr r3, _08066C18 @ =0x080BAFA6\n"
        "ldr r2, [r0, #0x00]\n"
        "ldr r4, _08066C1C @ =0x080BAF6A\n"
        "adds r5, r3, #0x0\n"
        "adds r5, #0x3A\n"
        "_08066C06:\n"
        "ldrb r0, [r6, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _08066C20\n"
        "ldr r1, [r2, #0x00]\n"
        "ldrh r0, [r4, #0x00]\n"
        "b _08066C24\n"
        ".byte 0x00, 0x00\n"
        "_08066C14: .4byte 0x030009A8\n"
        "_08066C18: .4byte 0x080BAFA6\n"
        "_08066C1C: .4byte 0x080BAF6A\n"
        "_08066C20:\n"
        "ldr r1, [r2, #0x00]\n"
        "ldrh r0, [r3, #0x00]\n"
        "_08066C24:\n"
        "strh r0, [r1, #0x18]\n"
        "adds r3, #0x02\n"
        "adds r2, #0x04\n"
        "adds r4, #0x02\n"
        "cmp r3, r5\n"
        "ble _08066C06\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

