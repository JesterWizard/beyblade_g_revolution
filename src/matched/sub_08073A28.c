#include "global.h"

// @ 0x08073a28
#include "global.h"

// @ 0x08073a28
void sub_08073A28(u8 *s, u8 c, u16 n)
{
    s32 len;
    s32 i;
    u16 orig;
    u8 *at;

    orig = n;
    if (s == 0)
        return;
    if (n == 0)
        return;
    len = sub_08073078(s);
    n = (u16)(n - 1);
    if ((s32)orig > len)
        return;
    i = len;
    at = s + n;
    if (i >= (s32)n)
    {
        do
        {
            s[i + 1] = s[i];
            i--;
        } while (i >= (s32)n);
    }
    *at = c;
}

