#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803715c
/* match-compiler: old_agbcc */
// score = experience-derived value of side b (0 = MainWork.expPoints, else
// gData_030002A0[b]) clamped to 20..100. Side a gets the score (divided by
// its unk24->unk04 when positive) and the other side a quarter; every total
// is capped at 0x3FFF. Returns the score.
s32 BtlApplyClampedScore(u8 a, u8 b)
{
    struct Unk3715C *slot;
    s32 score;
    s32 key;

    if (b == 0)
    {
        score = (s16)_080740B0(gData_03000198->expPoints, 10);
    }
    else
    {
        score = _080740B0(gData_030002A0[b].unk08, 10);
        gData_030002A0[b].unk28->unk26 += 5;
    }
    if (score <= 19)
        score = 20;
    if (score > 100)
        score = 100;

    if (a == 0)
    {
        key = sub_08042C3C((s8)_080672A8());
        if (gData_030002A0[b].unk24->unk04 > 0)
            score = Div(score, gData_030002A0[b].unk24->unk04);
        if (gData_03000198->expPoints < key || key == -1)
        {
            gData_03000198->expPoints += score;
            gData_030002A0[0].unk28->unk26 += 5;
        }
        else
        {
            score = RandRange(10) + 1;
        }
        if (gData_03000198->expPoints > 0x3FFF)
            gData_03000198->expPoints = 0x3FFF;
        slot = gData_030002A0[b].unk24;
        if (slot != NULL)
        {
            slot->unk00 += score >> 2;
            gData_030002A0[b].unk28->unk26 += 5;
            if (gData_030002A0[b].unk24->unk00 > 0x3FFF)
                gData_030002A0[b].unk24->unk00 = 0x3FFF;
        }
    }
    else
    {
        if (gData_030002A0[a].unk24 != NULL)
        {
            if (gData_030002A0[a].unk24->unk04 > 0)
                score = Div(score, gData_030002A0[a].unk24->unk04);
            gData_030002A0[a].unk24->unk00 += score;
            gData_030002A0[a].unk28->unk26 += 5;
            if (gData_030002A0[a].unk24->unk00 > 0x3FFF)
                gData_030002A0[a].unk24->unk00 = 0x3FFF;
        }
        gData_03000198->expPoints += score >> 2;
        gData_030002A0[0].unk28->unk26 += 5;
        if (gData_03000198->expPoints > 0x3FFF)
            gData_03000198->expPoints = 0x3FFF;
    }
    return score;
}

