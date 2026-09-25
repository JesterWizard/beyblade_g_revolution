#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

/* match-compiler: old_agbcc */

/* @ 0x08062AF8 — find-or-alloc 16-slot pool entry; palette via running 0x05000200
 * 144/162 same_size. First DIFF: early pool_loc keeps addr in r7 (retail uses r0
 * then reloads into r7 for second loop). Flag is 0x800 (0x80<<4), not 0x1000.
 */
s32 sub_08062AF8(void *table, void *key)
{
    void *table_reg;
    struct Unk62A74 **pool_loc;
    struct Unk62A74 *pool;
    void *entry;
    void **slot;
    s32 i;
    u32 one;
    u16 mask;
    u8 *dst;
    void **src_loc;
    void *src;
    u32 flags;

    table_reg = table;
    if (table_reg == 0)
        return -1;

    pool_loc = &gUnk_030008D0;
    pool = *pool_loc;
    if (pool == 0)
        return -1;

    /* (key << 2) before adding table base */
    entry = ((void **)table_reg)[(u32)key];

    slot = pool->unk00;
    for (i = 0; i <= 0x0F; i++)
    {
        if (*slot == entry)
            return (s8)i;
        slot++;
    }

    one = 1;
    dst = (u8 *)0x05000200;
    for (i = 0; i <= 0x0F; i++)
    {
        pool = *pool_loc;
        mask = pool->unk40;
        if (((mask >> i) & one) == 0)
        {
            pool->unk40 = (u16)(mask | (one << i));
            flags = gMainWorkPtr->unk1808;
            if ((flags & 0x800) == 0)
            {
                src_loc = (void **)gData_080BB8C0;
                src = *src_loc;
                _08073C4C(entry, dst, 0x20, src);
            }
            pool = *pool_loc;
            pool->unk00[i] = entry;
            return (s8)i;
        }
        dst += 0x20;
    }
    return -1;
}
