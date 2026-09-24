#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806114c
/* match-compiler: old_agbcc */
#include "global.h"

void sub_0806114C(struct Unk6114C *state, u32 tile, u32 palette, u32 first, u32 last)
{
    u16 palBits;
    u32 saved;
    u16 *addr;
    u16 mask;
    u32 base;
    u32 scaled;

    palBits = (u16)((palette << 28) >> 16);
    tile &= 0x1F;
    first &= 0x1F;
    saved = first;
    last &= 0x1F;
    if (last < first)
    {
        first = last;
        last = saved;
    }
    addr = (u16 *)(state->unk5C << 11);
    base = 0xC0;
    base <<= 19;
    addr = (u16 *)((u32)addr + base);
    addr = (u16 *)((u32)addr + (tile << 6));
    if ((s32)first <= (s32)last)
    {
        mask = 0x3FF;
        scaled = (first << 1) + (u32)addr;
        addr = (u16 *)scaled;
        do
        {
            *addr = (*addr & mask) | palBits;
            addr++;
            first++;
        } while ((s32)first <= (s32)last);
    }
}

