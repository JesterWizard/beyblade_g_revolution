#include "global.h"

// @ 0x08071e04
__attribute__((naked))
void sub_08071E04(struct Unk71E84 *p, void *a)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r3, r0, #0x0\n"
        "movs r4, #0x00\n"
        "movs r0, #0x01\n"
        "strb r0, [r3, #0x16]\n"
        "str r1, [r3, #0x00]\n"
        "movs r0, #0x00\n"
        "strh r4, [r3, #0x14]\n"
        "strb r0, [r3, #0x17]\n"
        "movs r0, #0x80\n"
        "lsls r0, r0, #0x01\n"
        "strh r0, [r3, #0x10]\n"
        "adds r1, #0x10\n"
        "str r1, [r3, #0x04]\n"
        "cmp r2, #0x7F\n"
        "bls _08071E26\n"
        "movs r2, #0x7F\n"
        "_08071E26:\n"
        "ldr r0, _08071E40 @ =0x030000C4\n"
        "ldr r1, [r0, #0x00]\n"
        "lsls r0, r2, #0x02\n"
        "adds r0, r0, r1\n"
        "ldr r0, [r0, #0x00]\n"
        "str r0, [r3, #0x08]\n"
        "str r4, [r3, #0x0C]\n"
        "str r4, [r3, #0x1C]\n"
        "str r4, [r3, #0x20]\n"
        "strh r4, [r3, #0x24]\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08071E40: .4byte 0x030000C4\n"
    );
}

