#include "global.h"

// @ 0x0803dd88
s32 sub_0803DD88(s32 a)
{
    register u32 r3 asm("r3") = 0x0807A1F4;
    register u32 r1 asm("r1");
    register u32 r2 asm("r2");

    asm("" : "+r"(r3));
    r1 = gMainWorkPtr->unk1818;
    r2 = r1 << 2;
    r1 = a << 2;
    r1 = r1 + a;
    r1 <<= 3;
    r2 = r2 + r1;
    r2 = r2 + r3;
    return *(s32 *)r2;
}
