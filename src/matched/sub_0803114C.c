#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803114c
// Lays out a row of entries: sub_0803139C fills up to 8 of them for `key`, then
// each non-NULL one gets x = base stepping by -0x900 (mode 0 starts from the far
// end so the row ends at base) and y = BattleWork.unkBB0.
void sub_0803114C(struct Sprite **entries, u32 key, u32 base, u32 modeArg)
{
    u8 mode = modeArg;
    s32 count = 0;
    s32 i = 0;
    s32 value;

    count = DigitSpritesSetValue(entries, key, 8, (void *)0x0810B208, count);
    if (mode == 0)
    {
        for (value = base + (count - 1) * 0x900; i < count; i++)
        {
            if (entries[i] != NULL)
            {
                entries[i]->unk08 = value;
                entries[i]->unk0C = gBattleWork->unkBB0;
            }
            value -= 0x900;
        }
    }
    else
    {
        for (value = base; i < count; i++)
        {
            if (entries[i] != NULL)
            {
                entries[i]->unk08 = value;
                entries[i]->unk0C = gBattleWork->unkBB0;
            }
            value -= 0x900;
        }
    }
}

