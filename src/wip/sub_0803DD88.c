/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x0803dd88
s32 sub_0803DD88(s32 a)
{
    u32 r3 = 0x0807A1F4;
    u32 r1;
    u32 r2;
r1 = gMainWorkPtr->unk1818;
    r2 = r1 << 2;
    r1 = a << 2;
    r1 = r1 + a;
    r1 <<= 3;
    r2 = r2 + r1;
    r2 = r2 + r3;
    return *(s32 *)r2;
}
