#include "global.h"
#include "ram_map.h"
#include "battle.h"

void sub_08030F38(void)
{
    struct BattleWork *volatile *loc = (struct BattleWork *volatile *)gBattleWorkPtrLoc;
    struct BattleWork *work;
    struct Unk705DC *e;
    s32 i;
    s32 delta;

    work = *loc;
    e = work->unk0AE8.fields.unkAF0;
    if (e != NULL && (s32)e->unk0C <= 0x7FF)
    {
        e->unk0C += 0x100;
        if (work->unk0AE8.fields.unkAF4 != NULL)
            work->unk0AE8.fields.unkAF4->unk0C += 0x100;
        work = *loc;
        if (work->unk0AE8.fields.unkAF8 != NULL)
            work->unk0AE8.fields.unkAF8->unk0C += 0x100;
        work = *loc;
        if (work->unk0AE8.fields.unkAFC != NULL)
            work->unk0AE8.fields.unkAFC->unk0C += 0x100;
        work = *loc;
        if (work->unk0AE8.fields.unkB40 != NULL)
            work->unk0AE8.fields.unkB40->unk0C += 0x100;
        work = *loc;
        if (work->unk0AE8.fields.unkB44 != NULL)
            work->unk0AE8.fields.unkB44->unk0C += 0x100;
        work = *loc;
        if (work->unkBA4 != NULL)
            work->unkBA4->unk0C += 0x100;
        work = *loc;
        if (work->unkBA8 != NULL)
            work->unkBA8->unk0C += 0x100;
        (*loc)->unkBB0 += 0x100;
        for (i = 0; i <= 7; i++)
        {
            work = *loc;
            if (work->unk0AE8.fields.unkB00[i] != NULL)
                work->unk0AE8.fields.unkB00[i]->unk0C = work->unkBB0;
            work = *loc;
            if (work->unk0AE8.fields.unkB20[i] != NULL)
                work->unk0AE8.fields.unkB20[i]->unk0C = work->unkBB0;
        }
    }
    work = *loc;
    e = work->unk0AE8.fields.unkB48;
    if (e != NULL && e->unk0C != work->unkBAC)
    {
        delta = work->unkBAC - e->unk0C;
        if (delta > 0x100)
            delta = 0x100;
        if (delta < 0x100) /* BUG: meant -0x100 */
            delta = -0x100;
        e->unk0C += delta;
        if (work->unk0AE8.fields.unkB4C != NULL)
            work->unk0AE8.fields.unkB4C->unk0C += delta;
    }
}