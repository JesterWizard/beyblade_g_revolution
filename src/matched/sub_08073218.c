#include "global.h"

// @ 0x08073218
s32 sub_08073218(u8 *src, u8 *dst, u32 n)
{
    u32 i = 0;

    if (src == 0 || dst == 0)
        return 0;

    for (;;)
    {
        u8 c;

        if (i < n)
            dst[i] = src[i];
        else
            dst[n - 1] = 0;

        c = src[i];
        i++;
        if (c == 0)
            break;
    }

    return i;
}

