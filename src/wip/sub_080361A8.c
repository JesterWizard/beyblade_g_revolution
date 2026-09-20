#include "global.h"

// @ 0x080361a8
void sub_080361A8(struct Unk361A8 *a)
{
    register u32 r3 = 12;
    register u32 r4 = 0xFFFF;
    register u32 r1;
    register u32 r2;

    r1 = a->unk1C;
    *(u32 *)&a->unk1C = r1;
    r2 = a->unk14;
    r1 = r1 - r2;
    r1 = (s32)(r1 * r3) >> 8;
    a->unk18 = r1;
    r2 = r2 + r1;
    r2 &= r4;
    a->unk14 = r2;
}
