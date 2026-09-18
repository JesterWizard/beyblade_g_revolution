#include "global.h"

// @ 0x0803593c
__attribute__((naked))
void sub_0803593C(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "ldr r4, [sp, #0x008]\n"
        "str r2, [r0, #0x0C]\n"
        "str r3, [r0, #0x10]\n"
        "str r4, [r0, #0x14]\n"
        "movs r3, #0x00\n"
        "str r3, [r0, #0x20]\n"
        "str r3, [r0, #0x1C]\n"
        "str r3, [r0, #0x18]\n"
        "str r3, [r0, #0x28]\n"
        "str r3, [r0, #0x24]\n"
        "ldr r2, _08035980 @ =0xFFFFFF00\n"
        "str r2, [r0, #0x2C]\n"
        "movs r2, #0x07\n"
        "str r2, [r0, #0x30]\n"
        "movs r2, #0x80\n"
        "lsls r2, r2, #0x05\n"
        "str r2, [r0, #0x04]\n"
        "str r2, [r0, #0x08]\n"
        "str r1, [r0, #0x00]\n"
        "movs r1, #0xE6\n"
        "str r1, [r0, #0x34]\n"
        "adds r1, #0xAA\n"
        "str r1, [r0, #0x38]\n"
        "str r3, [r0, #0x3C]\n"
        "str r3, [r0, #0x40]\n"
        "str r3, [r0, #0x44]\n"
        "subs r1, #0x2A\n"
        "str r1, [r0, #0x48]\n"
        "movs r1, #0x05\n"
        "str r1, [r0, #0x4C]\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08035980: .4byte 0xFFFFFF00\n"
    );
}

