#include "global.h"

// @ 0x08042b78
__attribute__((naked))
s32 sub_08042B78(s32 a)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r3, r0, #0x0\n"
        "ldr r2, _08042B98 @ =0x080908BC\n"
        "ldr r0, [r2, #0x00]\n"
        "movs r1, #0x01\n"
        "negs r1, r1\n"
        "cmp r0, r1\n"
        "beq _08042BA6\n"
        "adds r4, r1, #0x0\n"
        "adds r1, r2, #0x0\n"
        "_08042B8C:\n"
        "ldr r0, [r2, #0x00]\n"
        "cmp r0, r3\n"
        "bne _08042B9C\n"
        "ldr r0, [r1, #0x0C]\n"
        "b _08042BAA\n"
        ".byte 0x00, 0x00\n"
        "_08042B98: .4byte 0x080908BC\n"
        "_08042B9C:\n"
        "adds r1, #0x08\n"
        "adds r2, #0x08\n"
        "ldr r0, [r1, #0x00]\n"
        "cmp r0, r4\n"
        "bne _08042B8C\n"
        "_08042BA6:\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "_08042BAA:\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

