#include "global.h"

// @ 0x0807339c
void sub_0807339C(u8 *s)
{
    s32 n;

    if (s != 0)
    {
        n = sub_08073078(s);
        if (n != 0)
            s[n - 1] = 0;
    }
}

