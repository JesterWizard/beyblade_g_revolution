#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08073aec
// Copy NUL-terminated `src` into `dst`, expanding every `delim` byte into the
// string `repl`. At most `size` bytes are copied; past that each would-be
// write stores 0 at dst[size - 1] instead (and an overlong `repl` never
// advances, so it spins forever). Always NUL-terminates dst.
void StringExpandDelim(const u8 *src, u8 *dst, const u8 *repl, u8 delim, s32 size)
{
    s32 len;
    u8 ch;
    s32 j;

    len = 0;
    if (src == NULL || dst == NULL || repl == NULL || delim == 0)
        return;
    while (*src != 0)
    {
        ch = *src++;
        if (ch != delim)
        {
            if (len < size)
            {
                *dst++ = ch;
                len++;
            }
            else
            {
                dst[size - 1] = 0;
            }
        }
        else
        {
            for (j = 0; repl[j] != 0;)
            {
                if (len < size)
                {
                    *dst++ = repl[j++];
                    len++;
                }
                else
                {
                    dst[size - 1] = 0;
                }
            }
        }
    }
    *dst = 0;
}

