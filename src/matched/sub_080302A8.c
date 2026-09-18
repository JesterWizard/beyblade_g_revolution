#include "global.h"

// @ 0x080302a8
__attribute__((naked))
void sub_080302A8(struct Unk302A8 *a, struct Unk302A8Src *b)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "adds r4, r2, #0x0\n"
        "ldr r2, [r1, #0x08]\n"
        "negs r2, r2\n"
        "ldr r5, [r0, #0x00]\n"
        "ldr r1, [r0, #0x14]\n"
        "asrs r1, r1, #0x02\n"
        "ldr r0, [r5, #0x08]\n"
        "adds r0, r0, r1\n"
        "movs r3, #0x80\n"
        "lsls r3, r3, #0x03\n"
        "adds r0, r0, r3\n"
        "str r0, [r4, #0x08]\n"
        "ldr r0, [r5, #0x0C]\n"
        "adds r0, r0, r1\n"
        "adds r0, r0, r3\n"
        "str r0, [r4, #0x0C]\n"
        "lsls r2, r2, #0x08\n"
        "lsrs r2, r2, #0x10\n"
        "adds r0, r4, #0x0\n"
        "adds r1, r2, #0x0\n"
        "movs r3, #0x00\n"
        "bl sub_08070354\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

