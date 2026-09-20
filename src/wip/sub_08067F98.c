#include "global.h"

struct Unk67F98Entry *sub_08067F98(struct Unk67F98 *arg0, u16 key)
{
    struct Unk67F98Base *base;
    struct Unk67F98Entry *entry;
    u16 count;
    s32 i;

    base = arg0->unk00;
    entry = (struct Unk67F98Entry *)((u8 *)base + base->unk18);
    count = arg0->unk28;
    i = 0;

    for (; i < count; i++)
    {
        if (entry->unk00 == key)
            return entry;
        entry = (struct Unk67F98Entry *)((u8 *)entry + entry->unk02);
    }

    return 0;
}
