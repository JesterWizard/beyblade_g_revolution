#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061d68
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void sub_08061D68(u32 a, u32 b, u32 c, u32 d)
{
    u16 palBits;
    u32 saved;
    u16 *addr;
    u16 mask;
    u32 base;
    u32 scaled;

    palBits = (u16)((b << 28) >> 16);
    a &= 0x1F;
    c &= 0x1F;
    saved = c;
    d &= 0x1F;
    if (d < c)
    {
        c = d;
        d = saved;
    }
    addr = (u16 *)(gUnk_03000798->unk5C << 11);
    base = 0xC0;
    base <<= 19;
    addr = (u16 *)((u32)addr + base);
    addr = (u16 *)((u32)addr + (a << 6));
    if ((s32)c <= (s32)d)
    {
        mask = 0x3FF;
        scaled = (c << 1) + (u32)addr;
        addr = (u16 *)scaled;
        do
        {
            *addr = (*addr & mask) | palBits;
            addr++;
            c++;
        } while ((s32)c <= (s32)d);
    }
}

