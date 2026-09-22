/* match-flags: -fprologue-bugfix */
#include "global.h"

// @ 0x080739e8
s32 sub_080739E8(u8 *s)
{
    u8 c;
    u32 i;

    if (s == 0)
        return 0;

    c = s[0];
    i = 1;
    if (c == 0)
        return 0;

    while (c != 0)
    {
        if (c == 0x0A)
            return 1;
        c = s[i];
        i++;
    }

    if (s)
        return 0;
    else
        return 0;
}
