#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08038f30
// Shifts the battle scene by one step (dir -1 or 1): moves
// the four MainWork.unk07A4 entries and BattleWork.unk324 by 0x400, then either
// the four unk023C objects (sub_08070C98) or the unk2FC point set by 4.
// gMainWorkPtr is read through a volatile location: retail reloads it on every
// loop iteration.
void sub_08038F30(s32 dir)
{
    struct BattleWork **battle;
    struct Unk002A0Record *table;
    struct MainWork *volatile *work;
    s32 i;

    switch (dir)
    {
    case -1:
                i = 0;
        battle = gBattleWorkPtrLoc;
        table = gUnk_030002A0.records;
        work = (struct MainWork *volatile *)gMainWorkPtrLoc;
        for (; i <= 3; i++)
            (*work)->unk07A4[i]->unk0C -= 0x400;
        (*battle)->unk324->unk0C -= 0x400;
        if (table[(*battle)->activeRecordIdx].unk1C == 0)
        {
            for (i = 0; i <= 3; i++)
                TextGroupMoveBy((struct Unk70C98 *)&(*battle)->unk023C[i], 0, -4);
        }
        else
            Unk62044OffsetPoints(&(*battle)->unk2FC, 0, -4);
        break;
    case 1:
                i = 0;
        battle = gBattleWorkPtrLoc;
        table = gUnk_030002A0.records;
        work = (struct MainWork *volatile *)gMainWorkPtrLoc;
        for (; i <= 3; i++)
            (*work)->unk07A4[i]->unk0C += 0x400;
        (*battle)->unk324->unk0C += 0x400;
        if (table[(*battle)->activeRecordIdx].unk1C == 0)
        {
            for (i = 0; i <= 3; i++)
                TextGroupMoveBy((struct Unk70C98 *)&(*battle)->unk023C[i], 0, 4);
        }
        else
            Unk62044OffsetPoints(&(*battle)->unk2FC, 0, 4);
        break;
    }
}
