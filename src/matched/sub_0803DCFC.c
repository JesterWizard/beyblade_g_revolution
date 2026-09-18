#include "global.h"

// @ 0x0803dcfc
__attribute__((naked))
void *sub_0803DCFC(u32 i)
{
    asm(
        ".syntax unified\n"
        "push {lr}\n"
        "adds r2, r0, #0x0\n"
        "cmp r2, #0x52\n"
        "bls _0803DD18\n"
        "ldr r0, _0803DD10 @ =0x0833D1E0\n"
        "ldr r1, _0803DD14 @ =0x0833D1F4\n"
        "bl sub_08067B98\n"
        "movs r0, #0x00\n"
        "b _0803DD22\n"
        "_0803DD10: .4byte 0x0833D1E0\n"
        "_0803DD14: .4byte 0x0833D1F4\n"
        "_0803DD18:\n"
        "lsls r0, r2, #0x02\n"
        "adds r0, r0, r2\n"
        "lsls r0, r0, #0x03\n"
        "ldr r1, _0803DD28 @ =0x0807A1F4\n"
        "adds r0, r0, r1\n"
        "_0803DD22:\n"
        "pop {r1}\n"
        "bx r1\n"
        ".byte 0x00, 0x00\n"
        "_0803DD28: .4byte 0x0807A1F4\n"
    );
}

