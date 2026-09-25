#include "global.h"

// @ 0x0802d8dc
void HudRefreshStats(void)
{
    struct Unk026C *p;
    struct Unk310F0b *tens;
    struct Unk310F0b *ones;
    struct Unk42E78 *row;
    s8 t;

    _0802D9A8();
    p = gUnk_0300026C;
    if (p->unk0C != 0)
    {
        HudWriteDigits((struct Unk310F0b *)p->playerStrengthTens, (struct Unk310F0b *)p->playerStrengthOnes, gMainWorkPtr->strength);
        tens = (struct Unk310F0b *)gUnk_0300026C->playerLevelTens;
        ones = (struct Unk310F0b *)gUnk_0300026C->playerLevelOnes;
        t = ExpLevel();
        HudWriteDigits(tens, ones, t);
        if (gUnk_0300026C->playerExpBar != 0)
        {
            t = ExpBarFill(gMainWorkPtr->expPoints);
            gUnk_0300026C->playerExpBar->unk18 = t;
        }
    }
    p = gUnk_0300026C;
    if (p->unk28 != 0)
    {
        row = (struct Unk42E78 *)sub_08042E78(p->unk4E);
        p = gUnk_0300026C;
        HudWriteDigits((struct Unk310F0b *)p->bladeStrengthTens, (struct Unk310F0b *)p->bladeStrengthOnes, (s8)row->strength);
        tens = (struct Unk310F0b *)gUnk_0300026C->bitBeastLevelTens;
        ones = (struct Unk310F0b *)gUnk_0300026C->bitBeastLevelOnes;
        t = BitBeastLevel();
        HudWriteDigits(tens, ones, t);
        if (gUnk_0300026C->bitBeastExpBar != 0)
        {
            t = ExpBarFill(row->bitBeastExp);
            gUnk_0300026C->bitBeastExpBar->unk18 = t;
        }
    }
}

