#include "global.h"

// @ 0x08033574
/* match-compiler: old_agbcc */
void BtlEffectStop(void)
{
    struct BattleWork *w;
    u8 shifted;
    u8 *fieldPtr;

    w = gBattleWork;
    if (w->effectActive == 1)
    {
        fieldPtr = &w->unk1FE6;
        shifted = *fieldPtr >> 1;
        SceneObjFreeResources((struct Actor *)(fieldPtr - 0x3A));
        PaletteSlotRefRelease(shifted);
    }
    gBattleWork->effectMode = 0xFF;
    gBattleWork->effectActive = 0;
}

