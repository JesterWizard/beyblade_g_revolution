#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

extern s32 sub_08067584(u16 a, void *b);
extern void BtlClearUnk1688Entry(u32 a);

// @ 0x08044fb0
/* match-compiler: old_agbcc */
s32 sub_08044FB0(u32 index)
{
    void *base;
    u32 y;
    u32 yEnd;
    s32 streak;
    s32 hit;

    base = (u8 *)gMainWorkPtr->unk168C + index * 0x1F40;
    _08073C4C(0, base, 0xFB << 5, (void *)gData_080BB8BC[0]);
    y = index * 0x3EC + 3;
    yEnd = index * 0x3EC + 0x3EF;
    while (y < yEnd)
    {
        streak = 0;
        do
        {
            hit = sub_08067584((u16)y, base);
            streak++;
            if (hit == 0)
                streak = 0;
            if (streak == 8)
                break;
        } while (streak != 0);
        if (streak == 8)
        {
            DebugPrint((void *)0x083A2E30);
            BtlClearUnk1688Entry(index);
            sub_08044F64(index);
            return 0;
        }
        base = (u8 *)base + 8;
        y++;
    }
    return 1;
}
