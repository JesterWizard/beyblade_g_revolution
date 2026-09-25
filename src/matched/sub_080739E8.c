#include "global.h"

// @ 0x080739e8
__attribute__((naked))
s32 TextHasNewline(u8 *s)
{
    asm(
        ".syntax unified\n"
        "adds r1, r0, #0x0\n"
        "cmp r1, #0x00\n"
        "beq _08073A0A\n"
        "ldrb r0, [r1, #0x00]\n"
        "movs r2, #0x01\n"
        "cmp r0, #0x00\n"
        "beq _08073A08\n"
        "_080739F6:\n"
        "cmp r0, #0x0A\n"
        "bne _080739FE\n"
        "movs r0, #0x01\n"
        "b _08073A0A\n"
        "_080739FE:\n"
        "adds r0, r1, r2\n"
        "ldrb r0, [r0, #0x00]\n"
        "adds r2, #0x01\n"
        "cmp r0, #0x00\n"
        "bne _080739F6\n"
        "_08073A08:\n"
        "movs r0, #0x00\n"
        "_08073A0A:\n"
        "bx lr\n"
    );
}

