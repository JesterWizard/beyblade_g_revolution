#include "global.h"

s32 sub_08062AF8(void *table, void *key)
{
    void *table_reg;
    struct Unk62A74 *pool;
    void *entry;
    s32 i;

    table_reg = table;
    if (table_reg == 0)
        return -1;
    pool = gUnk_030008D0;
    if (pool == 0)
        return -1;
    entry = ((void **)table_reg)[(u32)key];
    for (i = 0; i <= 0x0F; i++)
    {
        if (pool->unk00[i] == entry)
            return i;
    }
    for (i = 0; i <= 0x0F; i++)
    {
        if (((pool->unk40 >> i) & 1) != 0)
            continue;
        pool->unk40 |= 1 << i;
        if ((gMainWorkPtr->unk1808 & 0x1000) == 0)
        {
            _08073C4C(
                entry,
                (void *)(0x05000200 + (i << 5)),
                0x20,
                *(void **)0x080BB8C0);
        }
        pool->unk00[i] = entry;
        return i;
    }
    return -1;
}
