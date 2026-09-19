#include "global.h"

// @ 0x0806b724
#include "global.h"

// @ 0x0806b724
s32 sub_0806B724(const u8 *s, const u8 *kern, s32 spacing)
{
    s32 total = 0;
    u8 c = *s++;

    if (c != 0)
    {
        do
        {
            s32 w = 5;

            if (c != 0x20)
            {
                const u8 *table = (const u8 *)0x080BB748;
                u8 idx = table[c];
                w = spacing;
                if (kern != 0)
                    w -= kern[idx];
            }

            total += w;
            c = *s++;
        } while (c != 0);
    }

    return total;
}

