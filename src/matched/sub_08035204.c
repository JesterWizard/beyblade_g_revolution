#include "global.h"

// @ 0x08035204
__attribute__((naked))
void sub_08035204(void *a, u32 b, u32 c, u32 d)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "mov r6, r8\n"
        "push {r6}\n"
        "adds r6, r0, #0x0\n"
        "adds r4, r1, #0x0\n"
        "adds r5, r2, #0x0\n"
        "mov r8, r3\n"
        "lsls r4, r4, #0x18\n"
        "lsrs r4, r4, #0x18\n"
        "lsls r5, r5, #0x18\n"
        "lsrs r5, r5, #0x18\n"
        "adds r1, r4, #0x0\n"
        "bl sub_08035258\n"
        "adds r0, r6, #0x0\n"
        "adds r1, r4, #0x0\n"
        "adds r2, r5, #0x0\n"
        "mov r3, r8\n"
        "bl sub_08035054\n"
        "pop {r3}\n"
        "mov r8, r3\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

