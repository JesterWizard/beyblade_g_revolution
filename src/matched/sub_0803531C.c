#include "global.h"

// @ 0x0803531c
void sub_0803531C(struct Unk35258 *a)
{
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");
    register u32 r5 asm("r5");

    if (a->unk1C.unk70 == 0)
        sub_08035258(a, 0);
    if (a->unk1D4.unk70 == 0)
        sub_08035258(a, 2);
    if (a->unkF8.unk70 == 0)
        sub_08035258(a, 1);

    r5 = (u32)&a->unk2C5;
    r0 = 1;
    r1 = *(u8 *)r5;
    r0 &= r1;
    if (r0 != 0)
        sub_08068418(&a->unk1C);

    r0 = 4;
    r1 = *(u8 *)r5;
    r0 &= r1;
    if (r0 != 0)
        sub_08068418(&a->unk1D4);

    r0 = 2;
    r5 = *(u8 *)r5;
    r0 &= r5;
    if (r0 != 0)
        sub_08068418(&a->unkF8);
}

