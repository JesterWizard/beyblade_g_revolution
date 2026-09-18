#include "global.h"

// @ 0x080726a4
__attribute__((naked))
void sub_080726A4(void *a, u32 b, u32 c, u32 d, u32 e)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, r7, lr}\n"
        "mov r7, r8\n"
        "push {r7}\n"
        "adds r5, r0, #0x0\n"
        "mov r8, r1\n"
        "adds r6, r2, #0x0\n"
        "adds r4, r3, #0x0\n"
        "ldr r7, [sp, #0x018]\n"
        "movs r0, #0x02\n"
        "negs r0, r0\n"
        "ands r6, r0\n"
        "ands r4, r0\n"
        "lsls r0, r4, #0x01\n"
        "muls r0, r7\n"
        "bl sub_0806A3A4\n"
        "str r0, [r5, #0x10]\n"
        "strh r6, [r5, #0x04]\n"
        "strh r4, [r5, #0x06]\n"
        "strh r7, [r5, #0x08]\n"
        "mov r1, r8\n"
        "str r1, [r5, #0x00]\n"
        "ldr r0, [r0, #0x00]\n"
        "str r0, [r5, #0x0C]\n"
        "pop {r3}\n"
        "mov r8, r3\n"
        "pop {r4, r5, r6, r7}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

