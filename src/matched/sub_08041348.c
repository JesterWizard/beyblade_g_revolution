#include "global.h"

// @ 0x08041348
__attribute__((naked))
void sub_08041348(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "movs r2, #0x92\n"
        "lsls r2, r2, #0x02\n"
        "adds r1, r0, r2\n"
        "ldr r3, [r1, #0x00]\n"
        "ldr r4, _0804138C @ =0x00000322\n"
        "adds r2, r0, r4\n"
        "movs r4, #0x00\n"
        "movs r1, #0x02\n"
        "strh r1, [r2, #0x00]\n"
        "movs r2, #0xC7\n"
        "lsls r2, r2, #0x02\n"
        "adds r1, r0, r2\n"
        "strh r4, [r1, #0x00]\n"
        "adds r1, r3, #0x0\n"
        "adds r1, #0x4C\n"
        "ldrh r2, [r1, #0x00]\n"
        "movs r4, #0xC8\n"
        "lsls r4, r4, #0x02\n"
        "adds r1, r0, r4\n"
        "strh r2, [r1, #0x00]\n"
        "adds r3, #0x4A\n"
        "ldrh r2, [r3, #0x00]\n"
        "ldr r3, _08041390 @ =0x0000031E\n"
        "adds r1, r0, r3\n"
        "strh r2, [r1, #0x00]\n"
        "subs r4, #0x49\n"
        "adds r0, r0, r4\n"
        "movs r1, #0x01\n"
        "strb r1, [r0, #0x00]\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_0804138C: .4byte 0x00000322\n"
        "_08041390: .4byte 0x0000031E\n"
    );
}

