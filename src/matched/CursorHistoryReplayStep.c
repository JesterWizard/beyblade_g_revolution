#include "global.h"

// @ 0x0804245c
/* match-compiler: old_agbcc */

void CursorHistoryReplayStep(void)
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

    index = (s8)gUnk_03000538->readIndex;
    value = gUnk_03000538->dir[(s32)index];
    switch (value)
    {
    case 1:
        CursorReplayStepRight();
        break;
    case 2:
        CursorReplayStepLeft();
        break;
    case 4:
        sub_08042630();
        break;
    case 8:
        sub_080426A4();
        break;
    }
    gUnk_03000538->readIndex = gUnk_03000538->readIndex + 1;
    {
        u8 *base;
        u8 *ring;
        u8 mask;
        u8 v;

        base = &gUnk_03000538->readIndex;
        ring = base;
        mask = 0x1F;
        v = *ring;
        mask &= v;
        *ring = mask;
    }
}


