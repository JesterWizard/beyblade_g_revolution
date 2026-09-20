#include "global.h"

// @ 0x08061c48
__attribute__((naked))
void sub_08061C48(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "ldr r4, _08061C78 @ =0x03000794\n"
        "ldr r0, [r4, #0x00]\n"
        "subs r0, #0x01\n"
        "cmp r0, #0x00\n"
        "blt _08061C70\n"
        "str r0, [r4, #0x00]\n"
        "ldr r5, _08061C7C @ =0x03000770\n"
        "lsls r0, r0, #0x03\n"
        "adds r0, r0, r5\n"
        "ldr r0, [r0, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _08061C70\n"
        "bl sub_0806A434\n"
        "ldr r0, [r4, #0x00]\n"
        "lsls r0, r0, #0x03\n"
        "adds r0, r0, r5\n"
        "movs r1, #0x00\n"
        "str r1, [r0, #0x00]\n"
        "_08061C70:\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08061C78: .4byte 0x03000794\n"
        "_08061C7C: .4byte 0x03000770\n"
    );
}

