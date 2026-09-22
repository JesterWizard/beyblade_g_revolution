#include "global.h"

void sub_0805E044(void *resource)
{
    struct Unk705DC *entry;
    struct Unk5E044Lookup *lookup;
    u32 offset;
    u32 index;

    if (resource == 0 || (gMainWorkPtr->unk1808 & 8) != 0)
        return;

    if (resource == (void *)0x08266DAC)
    {
        entry = gMainWorkPtr->unk0424;
        if (entry != 0)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }
    if (resource == (void *)0x0827EA3C)
    {
        entry = gMainWorkPtr->unk0424;
        if (entry != 0)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }
    if (resource == (void *)0x0826ADC8)
    {
        entry = gMainWorkPtr->unk0500;
        if (entry != 0)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }

    offset = 0;
    index = 0;
    while (*(u32 *)((u8 *)0x080991D0 + offset) != (u32)-1)
    {
        if ((void *)*(u32 *)((u8 *)0x080991D0 + offset) == resource)
        {
            lookup = (struct Unk5E044Lookup *)sub_08041DB4(index, 0);
            if (lookup != 0 && lookup->unkB8 != 0)
            {
                sub_0802D898(
                    lookup->unkB8->unk08,
                    lookup->unkB8->unk0C);
                sub_0802D8C4(1);
                return;
            }
        }
        offset += 4;
        index++;
    }
}
