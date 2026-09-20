#include "global.h"

void sub_08068798(struct Unk68798 *state)
{
    register struct Unk68798 *work;
    register s32 count;
    register s32 i;
    register struct Unk68798Entry *entry;
    register u32 offset;
    register struct Unk68798Entry *entries;
    register s32 value;
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
