#include "global.h"

// @ 0x08033530
void sub_08033530(void)
{
    if (gBattleWork->unk2088 == 1)
    {
        if (gBattleWork->unk201C == 0)
        {
            sub_08033574();
        }
        else
        {
            sub_080686D8(&gBattleWork->unk1FAC);
            sub_08068418(&gBattleWork->unk1FAC);
        }
    }
}

