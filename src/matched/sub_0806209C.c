#include "global.h"

// @ 0x0806209c
__attribute__((naked))
void sub_0806209C(struct Unk62044 *a)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "adds r5, r0, #0x0\n"
        "cmp r5, #0x00\n"
        "beq _080620CE\n"
        "ldr r0, [r5, #0x0C]\n"
        "cmp r0, #0x00\n"
        "beq _080620CA\n"
        "movs r6, #0x00\n"
        "_080620AC:\n"
        "ldr r0, [r5, #0x0C]\n"
        "lsls r4, r6, #0x02\n"
        "adds r0, r4, r0\n"
        "ldr r0, [r0, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _080620CA\n"
        "bl sub_0806FE84\n"
        "ldr r0, [r5, #0x0C]\n"
        "adds r0, r4, r0\n"
        "movs r1, #0x00\n"
        "str r1, [r0, #0x00]\n"
        "adds r6, #0x01\n"
        "cmp r6, #0x7F\n"
        "ble _080620AC\n"
        "_080620CA:\n"
        "movs r0, #0x00\n"
        "strh r0, [r5, #0x24]\n"
        "_080620CE:\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

