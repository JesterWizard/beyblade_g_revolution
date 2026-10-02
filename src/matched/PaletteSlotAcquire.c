#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08038438
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

// Acquire a palette slot for `palette`: find its table index, then either bump
// the refcount of the slot already holding it or claim the first free slot,
// copy the palette in and return the slot index (-1 if the pool is missing or
// full).
//
// The nested `do { } while (0)` wrappers are load-bearing. They add
// loop-depth weight so global alloc hands out r12/r8/r6/r7/r1/r2 as retail
// does, and they keep the two "found" blocks inside their loops (loop.c would
// otherwise move them out and hoist the gData_030003CC load).
s32 PaletteSlotAcquire(void *palette)
{
    s16 key;
    s16 i;

    key = 0;
    do { do { do {
    while (gData_08079068[(s16)key] != 0 && gData_08079068[(s16)key] != (u32)palette)
        key++;
    } while (0); } while (0); } while (0);
    if (gData_030003CC == NULL)
        return -1;
    i = 0;
    while (i < 16)
    {
        do { do { if ((s16)key == (s16)gData_030003CC->unk00[i])
        {
            gData_030003CC->unk22[i]++;
            return (s8)i;
        } } while (0); } while (0);
        do { do { i++; } while (0); } while (0);
    }
    for (i = 0; i < 16; i++)
    {
        do { if (((gData_030003CC->unk20 >> i) & 1) == 0)
        {
            gData_030003CC->unk00[i] = key;
            gData_030003CC->unk20 |= 1 << i;
            gData_030003CC->unk22[i] = 1;
            ((void (*)(u32, void *, u32))gData_080BB8C0[0])(gData_08079358[(s16)key], (void *)(0x05000200 + i * 32), 0x20);
            return (s8)i;
        } } while (0);
    }
    return -1;
}

