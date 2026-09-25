#include "global.h"
/* match-compiler: old_agbcc */
s32 sub_08073910(const u8 *src, u8 *dst, s32 size)
{
    s32 si;
    s32 di;
    u8 c;
    u8 *end;

    si = 0;
    di = 0;
    if (src == 0 || dst == 0)
        return 0;
    for (;;)
    {
        c = src[si];
        if (c != ' ')
            break;
        si++;
    }

    if (c == 0)
        return si;
    end = dst + size - 1;
    do
    {
        c = src[si];
        if (c == ' ')
            break;
        if (c == 0)
            break;
        if (di >= size)
            *end = 0;
        else
        {
            dst[di] = c;
            di++;
            si++;
        }
    } while (c != ' ' && c != 0 && c != 0x0A);
    if (di < size)
        dst[di] = 0;
    else
        *end = 0;
    return si;
}
