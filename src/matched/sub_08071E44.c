#include "global.h"

// @ 0x08071e44
__attribute__((naked))
void sub_08071E44(struct Unk71E84 *p, void *a)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "movs r4, #0x00\n"
        "ldsh r3, [r2, r4]\n"
        "lsls r3, r3, #0x02\n"
        "adds r3, r3, r1\n"
        "ldr r4, [r3, #0x00]\n"
        "movs r5, #0x00\n"
        "movs r6, #0x01\n"
        "strb r6, [r0, #0x16]\n"
        "str r4, [r0, #0x00]\n"
        "movs r3, #0x00\n"
        "strh r5, [r0, #0x14]\n"
        "strb r3, [r0, #0x17]\n"
        "movs r3, #0x80\n"
        "lsls r3, r3, #0x01\n"
        "strh r3, [r0, #0x10]\n"
        "adds r4, #0x10\n"
        "str r4, [r0, #0x04]\n"
        "ldr r3, _08071E80 @ =0x030000C4\n"
        "ldr r3, [r3, #0x00]\n"
        "ldr r3, [r3, #0x00]\n"
        "str r3, [r0, #0x08]\n"
        "str r5, [r0, #0x0C]\n"
        "str r1, [r0, #0x1C]\n"
        "str r2, [r0, #0x20]\n"
        "strh r6, [r0, #0x24]\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08071E80: .4byte 0x030000C4\n"
    );
}

