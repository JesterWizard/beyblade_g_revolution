#include "global.h"

// @ 0x08033084
#include "global.h"

void sub_080726E0(struct Unk726E0 *a, void *dst, s32 idx);

void sub_08033084(struct Unk726E0 *a, u32 flag)
{
    register struct Unk726E0 *dst asm("r5");
    register struct BattleWork **loc asm("r4");
    struct BattleWork *w;
    s32 value;

    dst = a;
    flag <<= 24;
    if (flag != 0)
    {
        loc = gBattleWorkPtrLoc;
        w = *loc;
        w->unk1F94 += w->unk1F90;
        value = w->unk1F94;
        if (value > 0x7FF)
        {
            value = 0x800;
            w->unk1F98 = 0;
        }
        if (value <= 0)
        {
            value = 0;
            (*loc)->unk1F98 = 0;
        }
        sub_080726E0(dst, (void *)0x05000000, value >> 8);
    }
}

