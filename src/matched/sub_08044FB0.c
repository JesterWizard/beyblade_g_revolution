#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08044fb0
// Clear save slot `index` (a 0x1F60-byte Unk45D3CEntry), then fill it from
// its 8-byte EEPROM blocks via sub_08067584, retrying a block while that
// returns nonzero. Eight failures in a row log, drop the slot and return 0.
s32 SaveSlotLoadFromEeprom(u32 index)
{
    u8 *base;
    u32 y;
    u32 start;
    u32 end;
    s32 streak;
    s32 hit;
    u32 blocks;

    base = (u8 *)&gMainWorkPtr->unk168C[index];
    {
        u32 *src = gData_080BB8BC;
        _08073C4C(0, base, sizeof(struct Unk45D3CEntry), (void *)*src);
    }
    blocks = sizeof(struct Unk45D3CEntry) / 8;
    start = index * blocks + 3;
    end = index * blocks + 0x3EF;
    for (y = start; y < end; y++)
    {
        streak = 0;
        do
        {
            hit = EepromReadBlock(y, base);
            streak++;
            if (hit == 0)
                streak = 0;
            if (streak == 8)
            {
                DebugPrint((void *)0x083A2E30);
                BtlClearUnk1688Entry(index);
                sub_08044F64(index);
                return 0;
            }
        } while (streak != 0);
        base += 8;
    }
    return 1;
}

