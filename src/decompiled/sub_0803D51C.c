/* match-compiler: old_agbcc */
#include "global.h"

s32 sub_0803D51C(void)
{
    s32 result;
    struct Unk2C314 out;

    result = 0;
    if ((gMainWorkPtr->unk1808 & 0x10000) != 0)
        return result;

    sub_0802C314(3, 1, &out);
    out.unk02 -= (u8)out.unk00 + (u8)gMainWorkPtr->unk0878;
    if ((s8)out.unk02 <= 0)
    {
        gUnk_030002A0.records[0].unk0C = 0;
        gBattleWork->unk130 = 1;
        result = 1;
        sub_0802C55C((s8)out.unk00, (s8)out.unk03, (s16)out.unk04);
        if (BtlUnk1694FindAndMark((s8)out.unk03) == 0)
            gBattleWork->unk1F73 = result;
    }

    sub_0802C314(2, 1, &out);
    out.unk02 -= (u8)out.unk00 + (u8)gMainWorkPtr->unk0878;
    if ((s8)out.unk02 <= 0)
    {
        gUnk_030002A0.records[0].unk0C = 0;
        gBattleWork->unk131 = 1;
        result = 1;
        sub_0802C55C((s8)out.unk00, (s8)out.unk03, (s16)out.unk04);
        if (BtlUnk1694FindAndMark((s8)out.unk03) == 0)
            gBattleWork->unk1F73 = result;
    }

    return result;
}
