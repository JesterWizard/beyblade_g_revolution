#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806a6f8
/* match-compiler: old_agbcc */
#include "global.h"

/* sub_0806A6F8 @ 0x0806A6F8 (436 bytes)
 * Battle input hub: play back / record a u16 key queue (gData_03003F64 == 2 / 1)
 * or poll REG_KEYINPUT, then refresh the ten Unk6A954 hold slots and the
 * new / previous / released key masks. */
void InputUpdate(void)
{
    u16 queueCount;
    u16 keys;
    u16 prev;
    u16 i;

    if (gData_03003F64 == 2)
    {
        if ((queueCount = gData_03004074) != 0)
        {
            keys = *gData_03004070++;
            gData_03004074 = queueCount - 1;
        }
        else
            gData_03003F64 = 0;
        gData_03004068 = gData_03000180.unk00;
    }

    if (gData_03003F64 != 2)
    {
        keys = ~REG_KEYINPUT;
        if ((keys & 0x3FF) != 0)
            gData_03004068 = gData_03000180.unk00;

        if (gData_03003F64 == 1)
        {
            if (gData_03004074 != 0)
            {
                *gData_03004070++ = keys;
                gData_03004074--;
            }
        }
    }

    gData_03004060 = keys & ~(prev = gData_03003F60);
    gData_0300406C = 0;
    gData_03004064 = prev;
    gData_03003F60 = keys;

    for (i = 0; i <= 9; i++)
    {
        if ((s32)(gData_03004060 & (1 << i)) > 0)
        {
            if (gData_03000180.unk00 > gData_03003F70[i].unk04 + gData_03003F70[i].unk0C)
                gData_03003F70[i].unk10 = 1;
            else
                gData_03003F70[i].unk10++;
            gData_03003F70[i].unk14 = gData_03003F70[i].unk00;
            gData_03003F70[i].unk00 = gData_03000180.unk00;
        }

        if ((s32)(gData_03003F60 & (1 << i)) > 0)
            gData_03003F70[i].unk08 = gData_03000180.unk00 - gData_03003F70[i].unk00;

        if (((gData_03003F60 >> i) & 1) == 0)
        {
            if ((s32)(gData_03004064 & (1 << i)) > 0)
            {
                u32 t;
                gData_03003F70[i].unk04 = t = gData_03000180.unk00;
                gData_03003F70[i].unk08 = t - gData_03003F70[i].unk00;
                gData_0300406C |= 1 << i;
            }
        }
    }
}

