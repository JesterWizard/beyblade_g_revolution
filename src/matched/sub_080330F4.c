#include "global.h"

// @ 0x080330f4
void BtlSetMode1F90(s32 a)
{
    gBattleWork->unk1F90 = a;
    gBattleWork->unk1F98 = 1;
    if (a >= 0)
        gBattleWork->unk1F94 = 0;
    else
        gBattleWork->unk1F94 = 0x800;
}

