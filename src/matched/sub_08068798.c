#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068798
#include "global.h"

void sub_08068798(struct Unk68798 *state)
{
    struct Unk68798 *work;
    s32 count;
    s32 i;
    struct Unk68798Entry *entry;
    u32 offset;
    struct Unk68798Entry *entries;
    s32 value;
    s32 delta;

    work = state;
    count = work->unk74;
    if (count == -1)
        return;
    for (i = 0; i < count; i++)
    {
        offset = i << 4;
        entries = work->unk78;
        entry = (struct Unk68798Entry *)((u8 *)entries + offset);
        value = (s32)(u32)entry->unk08;
        if (value != 0)
        {
            if (entry->unk00 == 0)
                continue;
            if (entry->unk04 <= 0)
                _08073C48(work, entry, (void *)(u32)value);
        }
        value = entry->unk00;
        if (value > 0)
        {
            delta = gUnk_03000180.unk00 - gUnk_03000180.unk04;
            if (entry->unk04 > 0)
                entry->unk04 -= delta;
            else
                entry->unk00 -= delta;
            if (entry->unk00 < 0)
                entry->unk00 = 0;
        }
    }
}

