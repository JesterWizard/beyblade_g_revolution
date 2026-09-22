/* match-compiler: old_agbcc */
#include "global.h"

void BgMapSetPaletteBankRun(u32 arg0, u32 arg1, u32 arg2, u32 arg3)
{
    u32 x;
    u16 palBits;
    u32 lo;
    u32 hi;
    u32 tmp;
    u16 *addr;
    s32 i;

    x = arg0 & 0x1F;
    palBits = (arg1 & 0xF) << 12;
    lo = arg2 & 0x1F;
    hi = arg3 & 0x1F;
    if (hi < lo)
    {
        tmp = lo;
        lo = hi;
        hi = tmp;
    }

    addr = (u16 *)(0x06000000 + (gUnk_03000798->unk5C << 0xB) + (x << 6));
    if (lo <= hi)
    {
        addr += lo;
        for (i = lo; i <= hi; i++)
        {
            *addr = (*addr & 0x3FF) | palBits;
            addr++;
        }
    }
}
