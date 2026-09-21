#include "global.h"

// @ 0x0804245c
/* match-compiler: old_agbcc */

void sub_0804245C(void)
{
    s8 index;
    u16 value;

    if (gMainWorkPtr->unk182C == 0)
        return;
    if (gMainWorkPtr->unk180C == 0 || gMainWorkPtr->unk180C == 0x10)
    {
        sub_080424E8();
        return;
    }

    index = (s8)gUnk_03000538->unk00;
    value = gUnk_03000538->unk04[(s32)index];
    switch (value)
    {
    case 1:
        sub_08042540();
        break;
    case 2:
        sub_080425B8();
        break;
    case 4:
        sub_08042630();
        break;
    case 8:
        sub_080426A4();
        break;
    }
    gUnk_03000538->unk00 = gUnk_03000538->unk00 + 1;
    {
        u8 *base;
        u8 *ring;
        u8 mask;
        u8 v;

        base = &gUnk_03000538->unk00;
        ring = base;
        mask = 0x1F;
        v = *ring;
        mask &= v;
        *ring = mask;
    }
}


