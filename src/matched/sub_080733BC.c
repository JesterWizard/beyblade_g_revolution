#include "global.h"

// @ 0x080733bc
void StringAppendChar(u8 *s, u32 c, u32 cap)
{
    u8 ch;
    s32 n;

    ch = c;
    if (s == 0)
        return;
    n = StringLength(s);
    if ((u32)(n + 1) < cap)
    {
        s[n] = ch;
        s[n + 1] = 0;
    }
}

