#include "global.h"

// @ 0x080712cc
__attribute__((naked))
void sub_080712CC(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, r7, lr}\n"
        "mov r7, r8\n"
        "push {r7}\n"
        "adds r7, r0, #0x0\n"
        "lsls r1, r1, #0x18\n"
        "lsrs r6, r1, #0x18\n"
        "ldr r5, [r7, #0x14]\n"
        "ldr r4, [r7, #0x1C]\n"
        "subs r4, #0x01\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "cmp r4, r0\n"
        "beq _080712F8\n"
        "mov r8, r0\n"
        "_080712E8:\n"
        "adds r0, r5, #0x0\n"
        "adds r1, r6, #0x0\n"
        "bl sub_080705A4\n"
        "ldr r5, [r5, #0x04]\n"
        "subs r4, #0x01\n"
        "cmp r4, r8\n"
        "bne _080712E8\n"
        "_080712F8:\n"
        "strb r6, [r7, #0x0E]\n"
        "pop {r3}\n"
        "mov r8, r3\n"
        "pop {r4, r5, r6, r7}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

