#include "global.h"

// @ 0x080603e0
void BtlSetAllUnk1710(u16 a)
{
    s16 i;

    i = 0;
    do
    {
        sub_08071FC8(gMainWorkPtr->unk1710[i], a);
        i++;
    } while (i <= 0x18);
    gMainWorkPtr->unk181A = a;
}

