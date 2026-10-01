#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803d51c
/* match-compiler: old_agbcc */
// Retail compiled this caller against a (s8, s8, s16) prototype of
// sub_0802C55C, whose definition takes (u16, u8, s16): the arguments are
// passed sign-extended. The cast reproduces that call (still a direct bl).
#define FreeSlotSigned ((void (*)(s32, s32, s32))CollectionFreeSlot)

// For the Unk1694 entries found by sub_0802C314(3, 1) and (2, 1): subtracts
// (unk00 + MainWork.strength) from the entry's unk02 and frees the entry once
// it drops to 0 or below. Returns 1 if either entry was freed.
s32 sub_0803D51C(void)
{
    struct Unk2C314 out;
    s32 result = 0;

    if (gMainWorkPtr->unk1808 & 0x10000)
        return 0;
    sub_0802C314(3, 1, &out);
    out.unk08->unk02 -= out.unk00 + gMainWorkPtr->strength;
    if ((s8)out.unk08->unk02 <= 0)
    {
        gUnk_030002A0.records[0].unk0C = result;
        gBattleWork->unk130 = 1;
        result = 1;
        FreeSlotSigned((s8)out.unk00, (s8)out.unk03, (s16)out.unk04);
        if (BtlUnk1694FindAndMark(out.unk03) == 0)
            gBattleWork->unk1F73 = result;
    }
    sub_0802C314(2, 1, &out);
    out.unk08->unk02 -= out.unk00 + gMainWorkPtr->strength;
    if ((s8)out.unk08->unk02 <= 0)
    {
        gUnk_030002A0.records[0].unk0C = 0;
        gBattleWork->unk131 = 1;
        result = 1;
        FreeSlotSigned((s8)out.unk00, (s8)out.unk03, (s16)out.unk04);
        if (BtlUnk1694FindAndMark(out.unk03) == 0)
            gBattleWork->unk1F73 = result;
    }
    return result;
}

