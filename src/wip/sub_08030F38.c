#include "global.h"

void sub_08030F38(void)
{
    register struct BattleWork **main_loc asm("r7");
    register struct BattleWork *work asm("r4");
    struct Unk705DC *resource;
    s32 i;
    s32 delta;

    main_loc = gBattleWorkPtrLoc;
    work = *main_loc;
    resource = work->unk0AE8.fields.unkAF0;
    if (resource != 0 && resource->unk0C <= 0x7FF)
    {
        resource->unk0C += 0x100;
        if (work->unk0AE8.fields.unkAF4 != 0)
            work->unk0AE8.fields.unkAF4->unk0C += 0x100;
        if (work->unk0AE8.fields.unkAF8 != 0)
            work->unk0AE8.fields.unkAF8->unk0C += 0x100;
        if (work->unk0AE8.fields.unkAFC != 0)
            work->unk0AE8.fields.unkAFC->unk0C += 0x100;
        if (work->unk0AE8.fields.unkB40 != 0)
            work->unk0AE8.fields.unkB40->unk0C += 0x100;
        if (work->unk0AE8.fields.unkB44 != 0)
            work->unk0AE8.fields.unkB44->unk0C += 0x100;
        if (work->unk0AE8.fields.unkB48 != 0)
            work->unk0AE8.fields.unkB48->unk0C += 0x100;
        if (work->unk0AE8.fields.unkB4C != 0)
            work->unk0AE8.fields.unkB4C->unk0C += 0x100;
        work->unkBB0 += 0x100;

        for (i = 0; i <= 7; i++)
        {
            if ((*main_loc)->unk0AE8.fields.unkB00[i] != 0)
                (*main_loc)->unk0AE8.fields.unkB00[i]->unk0C =
                    (*main_loc)->unkBB0;
            if ((*main_loc)->unk0AE8.fields.unkB20[i] != 0)
                (*main_loc)->unk0AE8.fields.unkB20[i]->unk0C =
                    (*main_loc)->unkBB0;
        }
    }

    resource = (*main_loc)->unk0AE8.fields.unkB48;
    if (resource != 0 && resource->unk0C != (*main_loc)->unkBAC)
    {
        delta = (*main_loc)->unkBAC - resource->unk0C;
        if (delta > 0x100)
            delta = 0x100;
        if (delta < -0x100)
            delta = -0x100;
        resource->unk0C += delta;
        if ((*main_loc)->unk0AE8.fields.unkB4C != 0)
            (*main_loc)->unk0AE8.fields.unkB4C->unk0C += delta;
    }
}
