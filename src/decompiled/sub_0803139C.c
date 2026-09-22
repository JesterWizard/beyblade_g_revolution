#include "global.h"

s32 sub_08038438(void *a);

s32 sub_0803139C(
    struct Unk67BB8 **array, s32 key, s32 count, void *table, u32 mode)
{
    struct Unk67BB8 **entries;
    struct Unk67BB8 *entry;
    s32 index;
    s32 quotient;
    s32 remainder;
    s32 remaining;
    u16 resource_id;
    u16 resource_type;

    entries = array;
    index = 0;
    quotient = 0;
    mode = (u8)mode;
    if (key != 0 && index < count)
    {
        do
        {
            quotient = Div(key, 10);
            remainder = key - quotient * 10;
            entry = *entries;
            if (entry == 0)
            {
                *entries = BtlObjPoolAlloc(0x1C2);
                if (*entries != 0)
                {
                    resource_id = (u16)sub_08038438(table);
                    sub_0806FF58(
                        *entries, table, 0, 0, (u32)entry, (u32)entry,
                        (u32)entry,
                        (u16)(index - 0x30));
                    if (*entries != 0)
                        TextEntrySetPaletteBank(
                            (struct Unk705DC *)*entries,
                            (u8)resource_id);
                }
            }
            if (*entries != 0)
                (*entries)->unk18 = (u16)remainder;
            key = quotient;
            index++;
            entries++;
        } while (quotient != 0 && index < count);
    }

    if (mode == 1)
    {
        entries = array + index;
        entry = *entries;
        if (entry == 0)
        {
            *entries = BtlObjPoolAlloc(0x1C2);
            if (*entries != 0)
            {
                resource_id = (u16)sub_08038438(table);
                sub_0806FF58(
                    *entries, table, 0, 0, (u32)entry, (u32)entry,
                    (u32)entry,
                    (u16)(index - 0x30));
                if (*entries != 0)
                    TextEntrySetPaletteBank(
                        (struct Unk705DC *)*entries,
                        (u8)resource_id);
            }
        }
        if (*entries != 0)
            (*entries)->unk18 = 10;
        index++;
    }

    entries = array + index;
    remaining = count - index;
    while (remaining > 0)
    {
        entry = *entries;
        if (entry != 0)
        {
            resource_type = entry->unk14 & 0xF000;
            resource_type >>= 12;
            sub_08038638(resource_type);
            BtlObjPoolFree(entry);
            *entries = 0;
        }
        entries++;
        remaining--;
    }
    return index;
}
