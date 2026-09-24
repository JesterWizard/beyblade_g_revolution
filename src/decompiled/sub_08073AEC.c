#include "global.h"

// @ 0x08073aec
void sub_08073AEC(void *a, void *b, void *c, u32 d, u32 e)
{
    u8 delim;
    u8 *src;
    u8 *dst;
    u8 *endMark;
    u8 *repl;
    u8 ch;
    u8 replCh;
    s32 len;

    delim = (u8)d;
    if (a == 0 || b == 0 || c == 0 || delim == 0)
    {
        if (b != 0)
            *(u8 *)b = 0;
        return;
    }
    src = a;
    dst = b;
    endMark = (u8 *)b + e - 1;
    len = 0;
    if (*src == 0)
    {
        *dst = 0;
        return;
    }
    for (;;)
    {
        ch = *src;
        src++;
        if (ch == delim)
        {
            repl = c;
            if (*(u8 *)repl == 0)
            {
                if (*src == 0)
                    break;
                continue;
            }
            endMark = (u8 *)b + e - 1;
            for (;;)
            {
                if (len >= e)
                {
                    *endMark = 0;
                    endMark++;
                }
                else
                {
                    replCh = *repl;
                    if (replCh == 0)
                        break;
                    *dst = replCh;
                    dst++;
                    endMark++;
                    len++;
                    repl++;
                }
                replCh = *repl;
                if (replCh == 0)
                    break;
            }
        }
        else
        {
            if (len >= e)
                *endMark = 0;
            else
            {
                *dst = ch;
                dst++;
                endMark++;
                len++;
            }
        }
        if (*src == 0)
            break;
    }
    *dst = 0;
}
