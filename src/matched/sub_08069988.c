#include "global.h"

// @ 0x08069988
__attribute__((naked))
void *sub_08069988(u8 a)
{
    asm(
        ".syntax unified\n"
        "lsls r0, r0, #0x18\n"
        "lsrs r0, r0, #0x18\n"
        "adds r1, r0, #0x0\n"
        "cmp r0, #0x01\n"
        "beq _080699B0\n"
        "cmp r0, #0x01\n"
        "bgt _0806999C\n"
        "cmp r0, #0x00\n"
        "beq _080699A6\n"
        "b _080699C2\n"
        "_0806999C:\n"
        "cmp r1, #0x02\n"
        "beq _080699B8\n"
        "cmp r1, #0x03\n"
        "beq _080699C0\n"
        "b _080699C2\n"
        "_080699A6:\n"
        "ldr r0, _080699AC @ =0x04000008\n"
        "b _080699C2\n"
        ".byte 0x00, 0x00\n"
        "_080699AC: .4byte 0x04000008\n"
        "_080699B0:\n"
        "ldr r0, _080699B4 @ =0x0400000A\n"
        "b _080699C2\n"
        "_080699B4: .4byte 0x0400000A\n"
        "_080699B8:\n"
        "ldr r0, _080699BC @ =0x0400000C\n"
        "b _080699C2\n"
        "_080699BC: .4byte 0x0400000C\n"
        "_080699C0:\n"
        "ldr r0, _080699C4 @ =0x0400000E\n"
        "_080699C2:\n"
        "bx lr\n"
        "_080699C4: .4byte 0x0400000E\n"
    );
}

