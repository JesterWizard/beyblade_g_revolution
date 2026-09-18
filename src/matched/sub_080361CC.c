#include "global.h"

// @ 0x080361cc
__attribute__((naked))
void sub_080361CC(void)
{
    asm(
        ".syntax unified\n"
        "adds r3, r1, #0x0\n"
        "ldr r1, [r0, #0x0C]\n"
        "asrs r1, r1, #0x08\n"
        "adds r2, r3, #0x0\n"
        "adds r2, #0x48\n"
        "strh r1, [r2, #0x00]\n"
        "ldr r1, [r0, #0x10]\n"
        "asrs r1, r1, #0x08\n"
        "adds r2, #0x02\n"
        "strh r1, [r2, #0x00]\n"
        "ldr r1, [r0, #0x00]\n"
        "str r1, [r3, #0x4C]\n"
        "ldr r1, [r0, #0x04]\n"
        "str r1, [r3, #0x50]\n"
        "ldr r1, [r0, #0x08]\n"
        "negs r1, r1\n"
        "str r1, [r3, #0x30]\n"
        "str r1, [r3, #0x34]\n"
        "ldr r0, [r0, #0x14]\n"
        "negs r0, r0\n"
        "str r0, [r3, #0x28]\n"
        "bx lr\n"
    );
}

