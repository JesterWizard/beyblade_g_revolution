/* match-compiler: old_agbcc */
#define RemoveBladeFromTysonsCollection sub_0803E0CC_x
#include "global.h"
#include "ram_map.h"
#undef RemoveBladeFromTysonsCollection

void RemoveBladeFromTysonsCollection(u16 id)
{
    s32 i;

    for (i = 0; i <= 0x52; i++)
    {
        if (gData_03000198->unk08D0[i].unk23 == (s16)id && gData_03000198->unk087C[i] == 1)
        {
            DebugPrint((void *)0x0833D34C, (void *)0x0833D358);
            gData_03000198->unk08D0[i].unk1D |= 0xFF;
            gData_03000198->unk08D0[i].unk21 |= 0xFF;
            gData_03000198->unk08D0[i].unk20 |= 0xFF;
            gData_03000198->unk08D0[i].unk26 = 0xFFFF;
            gData_03000198->unk08D0[i].unk1F |= 0xFF;
            gData_03000198->unk08D0[i].unk1C |= (s8)0xFF;
            gData_03000198->unk08D0[i].unk1E |= 0xFF;
            gData_03000198->unk08D0[i].unk23 |= 0xFF;
            gData_03000198->unk087C[i] = 0;
            gData_03000198->unk0877--;
            gData_03000198->unk1861[gData_03000198->unk08D0[i].unk1C]++;
        }
    }
}

