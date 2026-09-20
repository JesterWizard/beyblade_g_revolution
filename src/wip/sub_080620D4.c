#include "global.h"

void sub_080620D4(struct Unk62044 *a, s32 dx, s32 rawDy)
{
    s32 i;
    s32 shiftedDx;
    s32 shiftedDy;
    struct Unk620D4Entry **entries;
    struct Unk620D4Entry *entry;
    s32 first;

    if (a == 0)
        return;

    entries = a->unk0C;
    if (entries == 0)
        return;

    shiftedDx = dx << 8;
    shiftedDy = rawDy << 8;
    first = 0;
    for (i = 0; i <= 0x7F; i++)
    {
        entry = entries[i];
        if (entry == 0)
            break;

        entry->unk08 += shiftedDx;
        entry->unk0C += shiftedDy;

        if (!first)
        {
            a->unk10 = entries[0]->unk08;
            a->unk14 = entries[0]->unk0C;
            first = 1;
        }
    }
}
