#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08063104
#include "global.h"
#include "data_symbols.h"

// @ 0x08063104
void sub_08063104(void)
{
    void **slotA;
    void **slotB;
    void *srcA;
    u32 *d;

    slotA = &gUnk_030008DC;
    srcA = *slotA;
    if (srcA != 0)
    {
        slotB = &gUnk_030008E0;
        if (*slotB != 0)
        {
            d = gData_080BB8C0;
            _08073C4C(srcA, (void *)0x05000000, 0x200, (void *)d[0]);
            if (*slotB != 0)
            {
                HeapFree(*slotB);
                *slotB = 0;
            }
            *slotA = 0;
        }
    }
}

