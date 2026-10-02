#include "global.h"

// @ 0x0803D4C4
void sub_0803D4C4(void)
{
    s32 i;

    for (i = 0; i <= 0x2F; i++)
    {
        if (gBattleWork->unk0BCC[i].sprite != 0)
        {
            SceneObjMotionStep(&gBattleWork->unk0BCC[i]);
            if (gBattleWork->unk0BCC[i].posY > 0xA000)
                sub_08062238(&gBattleWork->unk0BCC[i]);
        }
    }
}

