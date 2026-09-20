#include "global.h"

// @ 0x08042b78
#include "global.h"

// @ 0x08042B78
s32 sub_08042B78(s32 a)
{
    register s32 key asm("r3");
    register s32 minusOne asm("r1");
    register s32 sentinel asm("r4");
    register const u32 *base asm("r2");
    register const u32 *entry asm("r1");
    s32 first;

    key = a;
    base = (const u32 *)0x080908BC;
    first = (s32)base[0];
    minusOne = -1;
    if (first != minusOne)
    {
        sentinel = minusOne;
        entry = base;
        for (;;)
        {
            if (base[0] == (u32)key)
                return entry[3];
            entry += 2;
            base += 2;
            if (entry[0] == (u32)sentinel)
                break;
        }
    }
    return -1;
}

