#include "global.h"

// @ 0x08047594
__attribute__((naked))
void sub_08047594(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "ldr r1, _080475BC @ =0x03000630\n"
        "ldr r0, [r1, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _080475B6\n"
        "movs r2, #0x00\n"
        "adds r4, r1, #0x0\n"
        "ldr r3, _080475C0 @ =0xFFFFC000\n"
        "_080475A4:\n"
        "ldr r0, [r4, #0x00]\n"
        "lsls r1, r2, #0x02\n"
        "adds r0, r0, r1\n"
        "ldr r0, [r0, #0x00]\n"
        "str r3, [r0, #0x08]\n"
        "str r3, [r0, #0x0C]\n"
        "adds r2, #0x01\n"
        "cmp r2, #0x0F\n"
        "ble _080475A4\n"
        "_080475B6:\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_080475BC: .4byte 0x03000630\n"
        "_080475C0: .4byte 0xFFFFC000\n"
    );
}

