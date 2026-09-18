#include "global.h"

// @ 0x080618a8
__attribute__((naked))
void sub_080618A8(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, r7, lr}\n"
        "adds r4, r0, #0x0\n"
        "adds r5, r1, #0x0\n"
        "ldr r0, [sp, #0x014]\n"
        "ldr r1, [sp, #0x018]\n"
        "lsls r2, r2, #0x10\n"
        "lsrs r6, r2, #0x10\n"
        "lsls r3, r3, #0x10\n"
        "lsrs r7, r3, #0x10\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r3, r0, #0x10\n"
        "lsls r1, r1, #0x10\n"
        "lsrs r2, r1, #0x10\n"
        "cmp r4, #0x00\n"
        "beq _080618E4\n"
        "cmp r5, #0x00\n"
        "beq _080618E4\n"
        "str r5, [r4, #0x00]\n"
        "movs r1, #0x00\n"
        "movs r0, #0x00\n"
        "strh r6, [r4, #0x08]\n"
        "strh r0, [r4, #0x10]\n"
        "strh r7, [r4, #0x12]\n"
        "strh r3, [r4, #0x0C]\n"
        "strh r2, [r4, #0x0E]\n"
        "strh r0, [r4, #0x0A]\n"
        "strb r1, [r4, #0x15]\n"
        "str r0, [r4, #0x04]\n"
        "movs r0, #0x01\n"
        "strb r0, [r4, #0x14]\n"
        "_080618E4:\n"
        "pop {r4, r5, r6, r7}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

