#include "global.h"

// @ 0x08042B28
__attribute__((naked))
void *sub_08042B28(u32 i)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r2, r0, #0x0\n"
        "ldr r0, _08042B48 @ =0x08091004\n"
        "lsls r1, r2, #0x02\n"
        "adds r4, r1, r0\n"
        "ldr r0, [r4, #0x00]\n"
        "cmp r0, #0x00\n"
        "bne _08042B40\n"
        "ldr r0, _08042B4C @ =0x083A2CD0\n"
        "adds r1, r2, #0x0\n"
        "bl sub_08067B98\n"
        "_08042B40:\n"
        "ldr r0, [r4, #0x00]\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
        "_08042B48: .4byte 0x08091004\n"
        "_08042B4C: .4byte 0x083A2CD0\n"
    );
}
