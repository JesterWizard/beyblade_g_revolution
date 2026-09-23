#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08060758
#include "global.h"
#include "data_symbols.h"

// @ 0x08060758
void sub_08060758(void)
{
    u32 *slotA;
    struct Unk0758 **slotB;
    void *p;
    struct Unk0758 *r;

    slotA = (u32 *)gUnk_03000754;
    *slotA = 0;
    slotB = gUnk_03000758Loc;
    *slotB = 0;
    p = HeapAlloc(0x0C);
    *slotA = (u32)p;
    if (p != 0)
    {
        *slotB = *(struct Unk0758 **)p;
        _08073C4C(0, *slotB, 0x0C, (void *)gData_080BB8BC[0]);
        r = *slotB;
        r->unk06 = 0;
    }
}

