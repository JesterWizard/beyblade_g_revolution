#include "global.h"

// @ 0x08042BE8
s32 sub_08042BE8(s32 a)
{
    register s32 key asm("r4");
    register u32 i asm("r3");
    register const u8 *base asm("r6");
    register const u8 *baseCopy asm("r7");
    register const u8 *valueBase asm("r5");
    register u32 off asm("r2");
    u32 next;

    key = a;
    i = 0;
    base = (const u8 *)0x080908BC;
    if (*(const s32 *)base != -1)
    {
        baseCopy = base;
        valueBase = base + 4;
        for (;;)
        {
            off = i << 3;
            next = i + 1;
            if (key < *(const s32 *)(valueBase + off))
            {
                if (key < *(const s32 *)(valueBase + (next << 3)))
                    return *(const s32 *)(baseCopy + off);
            }
            i = next;
            if (*(const s32 *)(base + (i << 3)) == -1)
                break;
        }
    }
    return -1;
}
