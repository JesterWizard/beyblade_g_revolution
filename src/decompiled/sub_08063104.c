#include "global.h"
#include "data_symbols.h"

// @ 0x08063104
void sub_08063104(void)
{
    void **slotA;
    void **slotB;
    void *srcA;

    slotA = &gUnk_030008DC;
    srcA = *slotA;
    if (srcA != 0)
    {
        slotB = &gUnk_030008E0;
        if (*slotB != 0)
        {
            _08073C4C(srcA, (void *)0x05000000, 0x200, (void *)gData_080BB8C0[0]);
            if (*slotB != 0)
            {
                sub_0806A434(*slotB);
                *slotB = 0;
            }
            *slotA = 0;
        }
    }
}
