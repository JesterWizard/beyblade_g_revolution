#include "global.h"

// @ 0x0806ac68
__attribute__((naked))
u32 sub_0806AC68(u8 *s)
{
    asm(
        ".syntax unified\n"
        "movs r2, #0x00\n"
        "b _0806AC74\n"
        "_0806AC6C:\n"
        "adds r0, #0x01\n"
        "cmp r1, #0x20\n"
        "beq _0806AC74\n"
        "adds r2, #0x01\n"
        "_0806AC74:\n"
        "ldrb r1, [r0, #0x00]\n"
        "cmp r1, #0x00\n"
        "bne _0806AC6C\n"
        "adds r0, r2, #0x0\n"
        "bx lr\n"
    );
}

