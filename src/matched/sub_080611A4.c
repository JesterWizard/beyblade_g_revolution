#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080611a4
#include "global.h"
#include "data_symbols.h"

// @ 0x080611a4
void VramSlotsInit(void)
{
    u32 *slotA;
    struct Unk0758 **slotB;
    void *p;

    slotA = (u32 *)gUnk_03000790;
    *slotA = 0;
    slotB = gUnk_03000798Loc;
    *slotB = 0;
    gUnk_03000794 = 0;
    p = HeapAlloc(0xAC);
    *slotA = (u32)p;
    if (p != 0)
    {
        *slotB = *(struct Unk0758 **)p;
        _08073C4C(0, *slotB, 0xAC, (void *)gData_080BB8BC[0]);
    }
    else
    {
        sub_080611F0();
    }
}

