#include "global.h"

// @ 0x0807339c
void StringRemoveLast(u8 *s)
{
    s32 n;

    if (s != 0)
    {
        n = StringLength(s);
        if (n != 0)
            s[n - 1] = 0;
    }
}

