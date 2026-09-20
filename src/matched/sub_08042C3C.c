#include "global.h"

// @ 0x08042c3c
#include "global.h"

// @ 0x08042C3C
s32 sub_08042C3C(s32 a)
{
    register s32 key asm("r3");
    register s32 minusOne asm("r1");
    register s32 sentinel asm("r4");
    register const u32 *entry asm("r2");
    const u32 *valueEntry;
    u32 first;

    key = a;
    entry = (const u32 *)0x0809094C;
    first = entry[0];
    minusOne = -1;
    if (first != (u32)minusOne)
    {
        sentinel = minusOne;
        valueEntry = entry;
        for (;;)
        {
            if (*entry == (u32)key)
                return valueEntry[1];
            valueEntry += 2;
            entry += 2;
            if (*valueEntry == (u32)sentinel)
                break;
        }
    }
    return -1;
}

