#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080733e4
// Appends string src to the end of string dst, a buffer of `size` bytes. A '\n'
// in src is not copied (that byte of dst is left as it was); bytes past the
// buffer are dropped and the last byte is forced to 0. Returns strlen(src), or
// -1 for a NULL argument or an already-full buffer.
s32 StringAppend(const u8 *src, u8 *dst, s32 size)
{
    u8 ch;
    u32 i = 0;

    if (src == NULL || dst == NULL)
        return -1;
    while (*dst != 0)
    {
        size--;
        dst++;
    }
    if (size > 0)
    {
        do
        {
            if (i < size)
            {
                ch = src[i];
                if (ch != '\n')
                    dst[i] = ch;
            }
            else
                dst[size - 1] = 0;
        } while (src[i++] != 0);
    }
    i--;
    return i;
}

