#include "global.h"

struct Unk3114C
{
    void *unk00;
    u8 filler_04[4];
    s32 unk08;
    s32 unk0C;
};

s32 sub_0803139C(
    struct Unk3114C **entries, s32 key, s32 count, void *table, s32 mode);

void sub_0803114C(void *array, u32 key, u32 base, u32 mode)
{
    struct Unk3114C **entries;
    s32 count;
    s32 value;
    s32 remaining;
    struct Unk3114C *entry;

    entries = (struct Unk3114C **)array;
    count = sub_0803139C(
        entries, key, 8, (void *)0x0810B208, 0);
    if ((u8)mode == 0)
    {
        value = base + (count - 1) * 0x900;
        remaining = count;
        while (remaining > 0)
        {
            entry = *entries;
            if (entry != 0)
            {
                entry->unk08 = value;
                entry->unk0C = gBattleWork->unkBB0;
            }
            value -= 0x900;
            entries++;
            remaining--;
        }
    }
    else
    {
        value = base;
        remaining = count;
        while (remaining > 0)
        {
            entry = *entries;
            if (entry != 0)
            {
                entry->unk08 = value;
                entry->unk0C = gBattleWork->unkBB0;
            }
            value -= 0x900;
            entries++;
            remaining--;
        }
    }
}
