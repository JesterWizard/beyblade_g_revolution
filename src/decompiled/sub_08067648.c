#include "global.h"

u16 sub_08067648(u16 value, u32 source_arg, u32 mode_arg)
{
    u16 scratch[0x4B];
    u16 *cursor;
    u16 *source;
    u8 count;
    u8 mode;
    u16 vcount;
    u16 previous;
    u16 current;
    u16 word;
    u16 remaining;
    u16 ready;
    s32 elapsed;
    u32 i;
    u32 j;

    source = (u16 *)source_arg;
    mode = (u8)mode_arg;
    if (value >= gUnk_030009B0->unk04)
        return 0x80FF;
    count = gUnk_030009B0->unk08;
    remaining = value;
    cursor = &scratch[count + 0x42];
    *cursor-- = 0;
    for (i = 0; i < 4; i++)
    {
        word = *source++;
        for (j = 0; j < 16; j++)
        {
            *cursor-- = word;
            word >>= 1;
        }
    }
    while (count != 0)
    {
        *cursor-- = remaining;
        remaining >>= 1;
        count--;
    }
    *cursor-- = 0;
    *cursor = 1;
    sub_08067504(scratch, (void *)0x0D000000, gUnk_030009B0->unk08 + 0x43);

    ready = 0;
    previous = REG_VCOUNT;
    elapsed = 0;
    for (;;)
    {
        if (ready == 0 && (*(vu16 *)0x0D000000 & 1) == 0)
        {
            current = REG_VCOUNT;
            if (current != previous)
            {
                if (current > previous)
                    elapsed += current - previous;
                else
                    elapsed += current + 0xE4 - previous;
                if (elapsed > 0x88)
                {
                    if (ready != 0)
                        return 0;
                    if ((*(vu16 *)0x0D000000 & 1) != 0)
                        return 0xC001;
                    return 0;
                }
                previous = current;
            }
        }
        if (ready == 0)
        {
            if ((*(vu16 *)0x0D000000 & 1) != 0)
                continue;
            ready++;
            if (mode == 0)
                return 0;
        }
    }
}
