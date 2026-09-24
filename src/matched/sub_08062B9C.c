#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062b9c
/* match-compiler: old_agbcc */
#include "global.h"

void sub_08062B9C(u32 arg0, u32 arg1)
{
    s32 hi;
    s32 lo;
    s32 i;
    s32 tmp;
    struct Unk62A74 *slot;

    lo = arg0 & 0xF;
    hi = arg1 & 0xF;
    tmp = hi;
    if ((u32)lo > (u32)hi)
    {
        hi = lo;
        lo = tmp;
    }

    for (i = lo; i <= hi; i++)
    {
        slot = gUnk_030008D0;
        slot->unk40 &= ~(1 << i);
        slot->unk00[i] = 0;
    }
}

