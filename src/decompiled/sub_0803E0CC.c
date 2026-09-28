/* match-compiler: old_agbcc */
#define sub_0803E0CC sub_0803E0CC_x
#include "global.h"
#include "ram_map.h"
#undef sub_0803E0CC

void sub_0803E0CC(u16 id)
{
    s32 i;

    for (i = 0; i <= 0x52; i++)
    {
        if (gMainWorkPtr->unk08D0[i].unk23 == (s16)id && gMainWorkPtr->unk087C[i] == 1)
        {
            sub_08067B98((void *)0x0833D34C, (void *)0x0833D358);
            gMainWorkPtr->unk08D0[i].unk1D |= 0xFF;
            gMainWorkPtr->unk08D0[i].unk21 |= 0xFF;
            gMainWorkPtr->unk08D0[i].unk20 |= 0xFF;
            gMainWorkPtr->unk08D0[i].unk26 = 0xFFFF;
            gMainWorkPtr->unk08D0[i].unk1F |= 0xFF;
            gMainWorkPtr->unk08D0[i].unk1C |= (u8)0xFF;
            gMainWorkPtr->unk08D0[i].unk1E |= 0xFF;
            gMainWorkPtr->unk08D0[i].unk23 |= 0xFF;
            gMainWorkPtr->unk087C[i] = 0;
            gMainWorkPtr->unk0877--;
            gMainWorkPtr->unk1861[gMainWorkPtr->unk08D0[i].unk1C]++;
        }
    }
}

