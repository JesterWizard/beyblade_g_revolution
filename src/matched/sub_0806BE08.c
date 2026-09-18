#include "global.h"

// @ 0x0806be08
__attribute__((naked))
s32 sub_0806BE08(struct Unk6BE08 *a, u32 b)
{
    asm(
        ".syntax unified\n"
        "ldr r2, [r0, #0x0C]\n"
        "subs r1, r1, r2\n"
        "lsrs r1, r1, #0x05\n"
        "ldr r0, [r0, #0x00]\n"
        "ldr r0, [r0, #0x08]\n"
        "cmp r1, r0\n"
        "bcc _0806BE1C\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "b _0806BE1E\n"
        "_0806BE1C:\n"
        "adds r0, r1, #0x0\n"
        "_0806BE1E:\n"
        "bx lr\n"
    );
}

