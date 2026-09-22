#include "global.h"

// @ 0x080617c4
#include "global.h"

/* match-flags: -fprologue-bugfix */

void TextSetActiveObject(struct Unk617C4 *a, u32 b)
{
    struct Unk617C4 *r2;
    u32 r0;
    u32 r3;
    u32 r1;
    struct Unk0798 *base;

    r2 = a;
    r0 = 1;
    r3 = r2->unk0C;
    r0 &= r3;
    if (r0 != 0)
    {
        base = gUnk_03000798;
        base->unk88 = r2;
        base->unk8C = b;
        r0 = r2->unk04;
        r1 = (u32)&base->unkA0;
        *(u16 *)r1 = r0;
        r0 = r2->unk05;
        r2 = (struct Unk617C4 *)&base->unkA2;
        *(u16 *)r2 = r0;
        r1 = *(u16 *)r1;
        r1 >>= 2;
        r0 = (u32)&base->unk9C;
        *(u16 *)r0 = r1;
    }
}

