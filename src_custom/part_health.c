#include "global.h"

/*
 * Retail sub_0803D51C. The equipped launcher (inventory type 3) and ripcord
 * (type 2) each store health in Unk1694.unk02, starting at 100. Every hit
 * subtracts the part id plus strength. At 0 or below the part is removed and
 * the launch RPM word is forced to 0.
 *
 * A set flag leaves that part's health byte alone. The other part still wears
 * exactly as retail does.
 */

static s32 WearPart(s8 type, u8 *brokenFlag)
{
    struct Unk2C314 out;
    struct Unk1694 *entry;
    u8 next;

    sub_0802C314(type, 1, &out);
    entry = out.unk08;
    next = (u8)(entry->unk02 - ((u8)out.unk00 + (u8)gMainWorkPtr->strength));
    entry->unk02 = next;
    if ((s8)next > 0)
        return 0;

    *(s32 *)(0x030002A0 + 0x0C) = 0;
    *brokenFlag = 1;
    sub_0802C55C((s8)out.unk00, (s8)out.unk03, (s16)out.unk04);
    if (sub_0802C5DC((u8)out.unk03) == 0)
        gBattleWork->unk1F73 = 1;
    return 1;
}

APPEND_TEXT s32 PartHealth__Replacement(void)
{
    s32 broken;

    if (gMainWorkPtr->unk1808 & 0x10000)
        return 0;

    broken = 0;
    if (gRuntimeConfig.infiniteLauncherHealth == FALSE)
        broken = WearPart(3, &gBattleWork->unk130);
    if (gRuntimeConfig.infiniteRipcordHealth == FALSE)
        broken |= WearPart(2, &gBattleWork->unk131);
    return broken;
}
