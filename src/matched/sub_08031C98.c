#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08031c98
// Tick side a->unk30C's BattleWork countdown. Once it has gone negative,
// drain that side's gData_030002A0 record (unk0C) and re-arm the countdown:
// 30 below 51 (10 below 21), otherwise unk18 * 10.
void sub_08031C98(struct Unk346C0 *a)
{
    struct BattleWork *bw = gBattleWork;

    if (bw->unk208C[a->unk30C] >= 0)
    {
        bw->unk208C[a->unk30C]--;
    }
    else
    {
        gData_030002A0[a->unk30C].unk0C--;
        if (gData_030002A0[a->unk30C].unk0C <= 0x32)
        {
            bw->unk208C[a->unk30C] = 0x1E;
            if (gData_030002A0[a->unk30C].unk0C <= 0x14)
                bw->unk208C[a->unk30C] = 0x0A;
        }
        else
        {
            bw->unk208C[a->unk30C] = gData_030002A0[a->unk30C].unk18 * 10;
        }
    }

    sub_080320CC();
    sub_08031204();
}

