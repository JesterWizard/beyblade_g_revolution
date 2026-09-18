#include "global.h"

// @ 0x08069a18
__attribute__((naked))
void sub_08069A18(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "ldr r4, [sp, #0x008]\n"
        "lsls r0, r0, #0x18\n"
        "lsrs r0, r0, #0x18\n"
        "lsls r1, r1, #0x10\n"
        "lsrs r1, r1, #0x10\n"
        "lsls r2, r2, #0x10\n"
        "lsrs r2, r2, #0x10\n"
        "lsls r3, r3, #0x10\n"
        "lsrs r3, r3, #0x10\n"
        "lsls r4, r4, #0x10\n"
        "lsrs r4, r4, #0x10\n"
        "cmp r0, #0x02\n"
        "beq _08069A3A\n"
        "cmp r0, #0x03\n"
        "beq _08069A44\n"
        "b _08069A54\n"
        "_08069A3A:\n"
        "ldr r0, _08069A40 @ =0x04000020\n"
        "b _08069A46\n"
        ".byte 0x00, 0x00\n"
        "_08069A40: .4byte 0x04000020\n"
        "_08069A44:\n"
        "ldr r0, _08069A5C @ =0x04000030\n"
        "_08069A46:\n"
        "strh r1, [r0, #0x00]\n"
        "adds r0, #0x02\n"
        "strh r2, [r0, #0x00]\n"
        "adds r0, #0x02\n"
        "strh r3, [r0, #0x00]\n"
        "adds r0, #0x02\n"
        "strh r4, [r0, #0x00]\n"
        "_08069A54:\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08069A5C: .4byte 0x04000030\n"
    );
}

