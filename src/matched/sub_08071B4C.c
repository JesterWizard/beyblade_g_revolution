#include "global.h"

// @ 0x08071b4c
__attribute__((naked))
void sub_08071B4C(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "ldr r0, _08071B8C @ =0x04000084\n"
        "movs r1, #0x00\n"
        "strh r1, [r0, #0x00]\n"
        "subs r0, #0x02\n"
        "strh r1, [r0, #0x00]\n"
        "adds r0, #0x42\n"
        "movs r4, #0x00\n"
        "str r4, [r0, #0x00]\n"
        "adds r0, #0x0C\n"
        "str r4, [r0, #0x00]\n"
        "adds r0, #0x34\n"
        "str r4, [r0, #0x00]\n"
        "subs r0, #0x04\n"
        "str r4, [r0, #0x00]\n"
        "ldr r3, _08071B90 @ =0x080BB8BC\n"
        "ldr r0, _08071B94 @ =0x030040DC\n"
        "ldr r1, [r0, #0x00]\n"
        "ldr r0, _08071B98 @ =0x0300410C\n"
        "ldrh r2, [r0, #0x00]\n"
        "lsls r0, r2, #0x01\n"
        "adds r0, #0x20\n"
        "adds r2, r2, r0\n"
        "ldr r3, [r3, #0x00]\n"
        "movs r0, #0x00\n"
        "bl _08073C4C\n"
        "ldr r0, _08071B9C @ =0x030000C0\n"
        "str r4, [r0, #0x00]\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08071B8C: .4byte 0x04000084\n"
        "_08071B90: .4byte 0x080BB8BC\n"
        "_08071B94: .4byte 0x030040DC\n"
        "_08071B98: .4byte 0x0300410C\n"
        "_08071B9C: .4byte 0x030000C0\n"
    );
}


