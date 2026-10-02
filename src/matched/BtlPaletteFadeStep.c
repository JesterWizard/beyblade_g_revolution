#include "global.h"

// @ 0x08033084

void PaletteAnimFrameCopy(struct Unk726E0 *a, void *dst, s32 idx);

void BtlPaletteFadeStep(struct Unk726E0 *a, u32 flag)
{
    struct Unk726E0 *dst;
    struct BattleWork **loc;
    struct BattleWork *w;
    s32 value;

    dst = a;
    flag <<= 24;
    if (flag != 0)
    {
        loc = gBattleWorkPtrLoc;
        w = *loc;
        w->fadeLevel += w->fadeStep;
        value = w->fadeLevel;
        if (value > 0x7FF)
        {
            value = 0x800;
            w->fadeActive = 0;
        }
        if (value <= 0)
        {
            value = 0;
            (*loc)->fadeActive = 0;
        }
        PaletteAnimFrameCopy(dst, (void *)0x05000000, value >> 8);
    }
}

