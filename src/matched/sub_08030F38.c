#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08030f38
// While the AF0 object's unk0C is at most 0x7FF, adds 0x100 to unk0C of the
// AF0..AFC/B40/B44/BA4/BA8 objects and to unkBB0, and sets the B00/B20 banks
// to unkBB0. Then moves the B48/B4C pair's unk0C towards unkBAC by 0x100.
void sub_08030F38(void)
{
    struct BattleWork *work;
    struct Sprite *e;
    s32 i;

    work = gData_03000290;
    e = work->unk0AE8.fields.unkAF0;
    if (e != NULL && (s32)e->unk0C <= 0x7FF)
    {
        e->unk0C += 0x100;
        if (work->unk0AE8.fields.unkAF4 != NULL)
            work->unk0AE8.fields.unkAF4->unk0C += 0x100;
        if (gData_03000290->unk0AE8.fields.unkAF8 != NULL)
            gData_03000290->unk0AE8.fields.unkAF8->unk0C += 0x100;
        if (gData_03000290->unk0AE8.fields.unkAFC != NULL)
            gData_03000290->unk0AE8.fields.unkAFC->unk0C += 0x100;
        if (gData_03000290->unk0AE8.fields.unkB40 != NULL)
            gData_03000290->unk0AE8.fields.unkB40->unk0C += 0x100;
        if (gData_03000290->unk0AE8.fields.unkB44 != NULL)
            gData_03000290->unk0AE8.fields.unkB44->unk0C += 0x100;
        if (gData_03000290->unkBA4 != NULL)
            gData_03000290->unkBA4->unk0C += 0x100;
        if (gData_03000290->unkBA8 != NULL)
            gData_03000290->unkBA8->unk0C += 0x100;
        gData_03000290->unkBB0 += 0x100;
        for (i = 0; i < 8; i++)
        {
            if (gData_03000290->unk0AE8.fields.unkB00[i] != NULL)
                gData_03000290->unk0AE8.fields.unkB00[i]->unk0C = gData_03000290->unkBB0;
            if (gData_03000290->unk0AE8.fields.unkB20[i] != NULL)
                gData_03000290->unk0AE8.fields.unkB20[i]->unk0C = gData_03000290->unkBB0;
        }
    }

    {
        struct BattleWork *battle;
        struct Sprite *lead;
        s32 delta;
        s32 step;

        battle = gData_03000290;
        lead = battle->unk0AE8.fields.unkB48;
        if (lead != NULL && lead->unk0C != battle->unkBAC)
        {
            delta = battle->unkBAC - lead->unk0C;
            step = 0x100;
            if (delta > step)
                delta = step;
            if (delta < step) /* BUG: meant -step */
                delta = -step;
            lead->unk0C += delta;
            if (battle->unk0AE8.fields.unkB4C != NULL)
                battle->unk0AE8.fields.unkB4C->unk0C += delta;
        }
    }
}

