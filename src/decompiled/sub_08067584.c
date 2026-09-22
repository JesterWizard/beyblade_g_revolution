#include "global.h"

s32 sub_08067584(u16 value_arg, void *out_arg)
{
    u16 value;
    u16 *out;
    struct Unk09B0 **global_loc;
    u16 *cursor;
    u8 i;
    u16 scratch[0x44];
    u8 count;
    u8 j;
    u32 packed;

    out = (u16 *)out_arg;
    value = value_arg;
    global_loc = (struct Unk09B0 **)0x030009B0;
    if (value >= (*global_loc)->unk04)
        return 0x80FF;
    count = (*global_loc)->unk08;
    cursor = &scratch[count + 1];
    for (i = 0; i < count; i++)
    {
        *cursor = value;
        cursor--;
        value >>= 1;
    }
    *cursor = 1;
    cursor--;
    *cursor = 1;
    sub_08067504(scratch, (void *)0x0D000000, count + 3);
    sub_08067504((void *)0x0D000000, scratch, 0x44);
    cursor = &scratch[4];
    out += 3;
    for (i = 0; i < 4; i++)
    {
        packed = 0;
        for (j = 0; j < 16; j++)
        {
            packed = (packed << 1) | (cursor[j] & 1);
        }
        *out = packed;
        out--;
        cursor += 16;
    }
    return 0;
}
