#include "global.h"

// @ 0x080615ec
__attribute__((naked))
void sub_080615EC(u16 x, u16 y)
{
    asm(
        ".syntax unified\n"
        "adds r2, r0, #0x0\n"
        "adds r3, r1, #0x0\n"
        "cmp r2, #0xEF\n"
        "bls _080615F6\n"
        "movs r2, #0x00\n"
        "_080615F6:\n"
        "cmp r3, #0x9F\n"
        "bls _080615FC\n"
        "movs r3, #0x00\n"
        "_080615FC:\n"
        "ldr r0, _0806160C @ =0x03000798\n"
        "ldr r0, [r0, #0x00]\n"
        "adds r1, r0, #0x0\n"
        "adds r1, #0x90\n"
        "strh r2, [r1, #0x00]\n"
        "adds r0, #0x92\n"
        "strh r3, [r0, #0x00]\n"
        "bx lr\n"
        "_0806160C: .4byte 0x03000798\n"
    );
}

