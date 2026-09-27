#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08073910
// Copy the next whitespace-delimited word of `src` into `dst` (at most `size`
// bytes incl. the terminator). Returns the index in `src` after the word.
s32 sub_08073910(const u8 *src, u8 *dst, s32 size_arg)
{
    u32 size = size_arg;
    u32 si;
    u32 di;
    u8 c;

    si = 0;
    di = 0;
    if (src == 0 || dst == 0)
        return 0;
    do
    {
        c = src[si];
        if (c == ' ')
            si++;
    } while (c == ' ');
    if (c == 0)
        return si;
    do
    {
        c = src[si];
        if (c != ' ' && c != 0)
        {
            if (di < size)
            {
                dst[di] = c;
                di++;
                si++;
            }
            else
                dst[size - 1] = 0;
        }
    } while (c != ' ' && c != 0 && c != '\n');
    if (di < size)
        dst[di] = 0;
    else
        dst[size - 1] = 0;
    return si;
}

