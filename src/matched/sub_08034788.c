#include "global.h"

// @ 0x08034788
__attribute__((naked))
void sub_08034788(void *a, u32 b, u32 *c, u32 *d)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "adds r4, r2, #0x0\n"
        "adds r5, r3, #0x0\n"
        "cmp r4, #0x00\n"
        "beq _080347AE\n"
        "cmp r5, #0x00\n"
        "beq _080347AE\n"
        "ldr r2, [r0, #0x00]\n"
        "ldr r3, [r1, #0x00]\n"
        "ldr r0, [r2, #0x0C]\n"
        "ldr r1, [r3, #0x0C]\n"
        "adds r0, r0, r1\n"
        "asrs r0, r0, #0x01\n"
        "str r0, [r4, #0x00]\n"
        "ldr r0, [r2, #0x10]\n"
        "ldr r1, [r3, #0x10]\n"
        "adds r0, r0, r1\n"
        "asrs r0, r0, #0x01\n"
        "str r0, [r5, #0x00]\n"
        "_080347AE:\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

