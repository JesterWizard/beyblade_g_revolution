#include "global.h"

// @ 0x08033530
void BtlSceneObjUpdate(void)
{
    if (gBattleWork->effectActive == 1)
    {
        if (gBattleWork->effectFramesLeft == 0)
        {
            BtlEffectStop();
        }
        else
        {
            sub_080686D8(&gBattleWork->effectObj);
            SceneObjUpdate(&gBattleWork->effectObj);
        }
    }
}

