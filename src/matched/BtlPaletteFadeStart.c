#include "global.h"

// @ 0x080330f4
void BtlPaletteFadeStart(s32 a)
{
    gBattleWork->fadeStep = a;
    gBattleWork->fadeActive = 1;
    if (a >= 0)
        gBattleWork->fadeLevel = 0;
    else
        gBattleWork->fadeLevel = 0x800;
}

