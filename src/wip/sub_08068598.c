#include "global.h"

void sub_08068598(struct Unk68598 *state)
{
    struct Unk68598 *work;
    struct Unk68598Record *record;
    u16 record_start;
    u16 record_length;
    struct Unk68014 *base;
    struct Unk68598Lookup *lookup;
    u16 value;
    s32 total;
    u16 flags;

    work = state;
    base = work->unk00;
    record = (struct Unk68598Record *)(
        (u8 *)base + (work->unk20 << 3) + 0x20);
    lookup = 0;
    if ((work->unk98 & 4) == 0)
    {
        lookup = (struct Unk68598Lookup *)(
            (u8 *)base + (base->unk08 << 3) + 0x20);
        if ((u8 *)lookup == (u8 *)base + base->unk18)
            lookup = 0;
    }
    total = work->unk34 + work->unk36;
    if (lookup != 0)
        total += lookup->values[work->unk22];
    value = total;
    if (value < gUnk_03000180.unk08)
        value = gUnk_03000180.unk08;
    if (gUnk_03000180.unk00 - work->unk58 < value)
        return;
    work->unk58 += value;
    record_start = record->value;
    record_length = record->unk02;
    work->unk60 = work->unk22;
    if ((work->unk33 & 2) != 0)
        work->unk22--;
    else
        work->unk22++;
    if ((s16)work->unk22 > (s16)(record_start - 1 + record_length))
    {
        flags = record->value;
        if ((flags & 1) != 0)
        {
            flags ^= 2;
            record->value = (record->value & 0xFF00) | flags;
            work->unk22 = record_start + record_length - 2;
        }
        else
        {
            work->unk22 = record_start;
        }
        work->unk24++;
    }
    if ((s16)work->unk22 < (s16)record_start)
    {
        flags = record->value;
        if ((flags & 1) != 0)
        {
            flags ^= 2;
            record->value = (record->value & 0xFF00) | flags;
            work->unk22 = record_start + 1;
        }
        else
        {
            work->unk22 = record_start + record_length - 1;
        }
        work->unk24++;
    }
    if (work->unk32 != 0 && work->unk24 >= work->unk32)
        sub_08068118((struct Unk68118 *)work);
}
