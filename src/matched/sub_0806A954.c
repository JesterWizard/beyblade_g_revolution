#include "global.h"

// @ 0x0806a954
__attribute__((naked))
void *sub_0806A954(u8 a)
{
    asm(
        ".syntax unified\n"
        "lsls r0, r0, #0x18\n"
        "lsrs r1, r0, #0x18\n"
        "cmp r1, #0x09\n"
        "bhi _0806A96C\n"
        "lsls r0, r1, #0x01\n"
        "adds r0, r0, r1\n"
        "lsls r0, r0, #0x03\n"
        "ldr r1, _0806A968 @ =0x03003F70\n"
        "adds r0, r0, r1\n"
        "b _0806A96E\n"
        "_0806A968: .4byte 0x03003F70\n"
        "_0806A96C:\n"
        "movs r0, #0x00\n"
        "_0806A96E:\n"
        "bx lr\n"
    );
}

