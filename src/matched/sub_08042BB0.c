#include "global.h"

// @ 0x08042bb0
#include "global.h"

// @ 0x08042BB0
s32 sub_08042BB0(s32 a)
{
    register s32 key asm("r3");
    register s32 minusOne asm("r1");
    register s32 sentinel asm("r4");
    register const u32 *base asm("r2");
    register const u32 *entry asm("r2");
    register const u32 *valueEntry asm("r1");
    u32 first;

    key = a;
    base = (const u32 *)0x080908BC;
    first = base[0];
    minusOne = -1;
    if (first != (u32)minusOne)
    {
        sentinel = minusOne;
        entry = base;
        valueEntry = base;
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

