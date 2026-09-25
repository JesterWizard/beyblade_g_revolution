#include "global.h"

// @ 0x08042BE8
s32 ExpBracket(s32 points)
{
    s32 key;
    u32 i;
    const u8 *base;
    const u8 *baseCopy;
    const u8 *valueBase;
    u32 off;
    u32 next;

    key = points;
    i = 0;
    base = (const u8 *)0x080908BC;
    if (*(const s32 *)base != -1)
    {
        baseCopy = base;
        valueBase = base + 4;
        for (;;)
        {
            off = i << 3;
            next = i + 1;
            if (key < *(const s32 *)(valueBase + off))
            {
                if (key < *(const s32 *)(valueBase + (next << 3)))
                    return *(const s32 *)(baseCopy + off);
            }
            i = next;
            if (*(const s32 *)(base + (i << 3)) == -1)
                break;
        }
    }
    return -1;
}
