#include "global.h"

// @ 0x08033878
void BattleScorePopupClear(void)
{
    s32 zero;

    zero = 0;
    gBattleWork->popupShown = zero;
    gBattleWork->popupTarget = zero;
    gBattleWork->popupActive = zero;
    gBattleWork->popupTargetY = zero;
    gBattleWork->popupTimer = zero;

    for (zero = 0; zero <= 3; zero++)
    {
        if (gBattleWork->popupDigits[zero] != 0)
        {
            BtlObjPoolFree(gBattleWork->popupDigits[zero]);
            gBattleWork->popupDigits[zero] = 0;
        }
    }
}

