#include "global.h"

struct Unk2E2F8
{
    s16 unk00;
    s16 unk02;
    u8 filler_04[2];
    u16 unk06;
    u8 filler_08[4];
};

s32 sub_0802E2F8(u16 a, u16 b, s32 multiplier)
{
    register s32 scale;
    register s32 value_a;
    register s32 lower_bound;
    register s32 limit;
    register struct Unk2E2F8 *table;
    register struct Unk2E2F8 *reset_table;
    register struct Unk2E2F8 *entry;
    s32 offset;
    s32 value_b;
    s32 amount;
    s32 result;

    scale = multiplier;
    table = (struct Unk2E2F8 *)0x08077AC0;
    limit = -1;
    if (table->unk00 <= limit)
        return 10;

    reset_table = table;
    value_a = (s16)a;
    value_b = (s16)b;
    lower_bound = limit;
    offset = 0;
    do
    {
        entry = (struct Unk2E2F8 *)(
            (u8 *)table + offset);
        if (entry->unk00 == value_a && entry->unk02 == value_b)
        {
            amount = (s32)((u32)entry->unk06 << 16);
            if (amount > 0)
            {
                amount = (amount >> 17) * scale;
                result = _080740B0(amount, 100);
                if (result > 0)
                    return result;
                return 2;
            }
        }
        offset += 12;
        table = reset_table;
        entry = (struct Unk2E2F8 *)(
            (u8 *)table + offset);
    } while (entry->unk00 > lower_bound);
    return 10;
}
