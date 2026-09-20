#include "global.h"

// @ 0x08033878
void sub_08033878(void)
{
    s32 zero;

    zero = 0;
    gBattleWork->unk0B64 = zero;
    gBattleWork->unk0B68 = zero;
    gBattleWork->unk0B6C = zero;
    gBattleWork->unk0B70 = zero;
    gBattleWork->unk0B78 = zero;

    for (zero = 0; zero <= 3; zero++)
    {
        if (gBattleWork->unk0B54[zero] != 0)
        {
            sub_0806FE84(gBattleWork->unk0B54[zero]);
            gBattleWork->unk0B54[zero] = 0;
        }
    }
}

