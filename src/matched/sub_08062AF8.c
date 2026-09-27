#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062af8
/* match-compiler: old_agbcc */
// Find `table[key]` in the 16-slot palette pool, or claim a free slot, upload
// the 32-byte palette to OBJ palette RAM and return the slot index (-1 if full).
s32 sub_08062AF8(void *table, void *key)
{
    void **slot;
    void *entry;
    s32 i;
    u32 one;
    struct Unk62A74 **loc;
    u16 mask;
    u8 *dst;

    if (table == 0)
        return -1;
    if (gUnk_030008D0 == 0)
        return -1;
    entry = ((void **)table)[(u32)key];

    slot = gUnk_030008D0->unk00;
    for (i = 0; i <= 0x0F; i++)
    {
        if (*slot == entry)
            return (s8)i;
        slot++;
    }

    i = 0;
    loc = &gUnk_030008D0;
    one = 1;
    dst = (u8 *)0x05000200;
    for (; i <= 0x0F; i++)
    {
        mask = (*loc)->unk40;
        if (((mask >> i) & one) == 0)
        {
            (*loc)->unk40 = mask | (one << i);
            if ((gMainWorkPtr->unk1808 & 0x800) == 0)
                _08073C4C(entry, dst, 0x20, (void *)gData_080BB8C0[0]);
            (*loc)->unk00[i] = entry;
            return (s8)i;
        }
        dst += 0x20;
    }
    return -1;
}

