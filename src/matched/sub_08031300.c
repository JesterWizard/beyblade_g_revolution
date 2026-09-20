#include "global.h"

// @ 0x08031300
void sub_08031300(struct Unk312EC *a)
{
    register struct Unk312EC *r2 asm("r2");
    register s32 r3 asm("r3");
    register struct Unk705DC *r4 asm("r4");
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");

    r2 = a;
    r0 = r2->unk08;
    if (r0 == 0)
        return;
    r0 = r2->unk04;
    if ((s32)r0 < 0)
        goto neg;
    r3 = (s32)r0 - 1;
    r2->unk04 = r3;
    r4 = r2->unk0C;
    if (r4 == 0)
        return;
    r0 = r4->unk14;
    r1 = r0 >> 0xC;
    r0 = 5;
    r3 &= r0;
    if (r3 != 0)
        return;
    r0 = 1;
    r0 = (s32)r2->unk01;
    if (r1 != r0)
        goto use_unk01;
    r1 = 0;
    r1 = (s32)r2->unk00;
    goto call;
use_unk01:
    r1 = r0;
call:
    r1 = (u8)r1;
    r0 = (u32)r4;
    sub_080705DC((struct Unk705DC *)r0, (s32)r1);
    return;
neg:
    r0 = (u32)r2;
    sub_080312D8((struct Unk312EC *)r0);
}

