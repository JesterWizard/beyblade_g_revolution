#include "global.h"

// @ 0x08038314
void sub_08038314(struct Unk38314 *a, s32 b)
{
    s32 count;

    count = a->unk2FC - 1;
    a->unk2FC = count;
    if (count > 0)
    {
        if ((gBtlKeysHeld & 3) == 0)
            return;
    }
    a->unk304 = b;
    sub_08062044(&gBattleWork->unk19C[0]);
    sub_08062044(&gBattleWork->unk19C[1]);
    sub_08062044(&gBattleWork->unk19C[2]);
    sub_08062044(&gBattleWork->unk19C[3]);
}
