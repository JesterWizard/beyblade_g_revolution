#include "global.h"

// @ 0x0803715c
s32 BtlApplyClampedScore(u8 a, u8 b)
{
    struct Unk002A0Record *rec;
    struct Unk3715C *slot;
    s32 score;
    s32 key;

    if (b == 0)
        score = (s16)_080740B0(gMainWorkPtr->expPoints, 10);
    else
    {
        rec = &gUnk_030002A0.records[b];
        score = _080740B0(rec->unk08, 10);
        rec->unk28->unk26 += 5;
    }
    if (score <= 19)
        score = 20;
    if (score > 100)
        score = 100;

    if (a == 0)
    {
        key = sub_08042C3C((s8)_080672A8());
        slot = gUnk_030002A0.records[b].unk24;
        if (slot->unk04 > 0)
            score = Div(score, slot->unk04);
        if (gMainWorkPtr->expPoints < key || key == -1)
        {
            gMainWorkPtr->expPoints += score;
            gUnk_030002A0.records[0].unk28->unk26 += 5;
        }
        else
            score = RandRange(10) + 1;
        if (gMainWorkPtr->expPoints > 0x3FFF)
            gMainWorkPtr->expPoints = 0x3FFF;
        slot = gUnk_030002A0.records[b].unk24;
        if (slot != 0)
        {
            slot->unk00 += score >> 2;
            gUnk_030002A0.records[b].unk28->unk26 += 5;
            if (slot->unk00 > 0x3FFF)
                slot->unk00 = 0x3FFF;
        }
    }
    else
    {
        rec = &gUnk_030002A0.records[a];
        slot = rec->unk24;
        if (slot != 0)
        {
            if (slot->unk04 > 0)
                score = Div(score, slot->unk04);
            slot->unk00 += score;
            rec->unk28->unk26 += 5;
            if (slot->unk00 > 0x3FFF)
                slot->unk00 = 0x3FFF;
        }
        gMainWorkPtr->expPoints += score >> 2;
        gUnk_030002A0.records[0].unk28->unk26 += 5;
        if (gMainWorkPtr->expPoints > 0x3FFF)
            gMainWorkPtr->expPoints = 0x3FFF;
    }
    return score;
}
