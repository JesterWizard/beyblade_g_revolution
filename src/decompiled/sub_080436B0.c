/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

extern struct Unk0554 *gData_03000554;
extern struct Unk0558 *gData_03000558;
extern u16 gData_03003F60;
void sub_080436B0(void)
{
    u8 phase;
    s32 *pos;
    struct Unk0554 *st;

    switch (phase = gData_03000554->unk01)
    {
    case 0:
        if (gData_03003F60 & 0x40)
        {
            if ((gData_03000554->unk02 & 0x10) && gData_03000558->unk04 != NULL)
        {
            if (gData_03000558->unk34[0] >= 0)
            {
                pos = (s32 *)sub_0806DEF4((struct Unk6DEF4 *)sub_08062A14(), gData_03000558->unk34[0]);
                gData_03000554->unk04 = pos[0] >> 3;
                gData_03000554->unk06 = (pos[1] >> 3) - 16;
            }
            gData_03000198->unk17F6 = gData_03000558->unk04->unk01;
            gData_03000554->unk01 = 1;
            gData_03000554->unk00 = phase;
            sub_080435D8();
        }
        }
        else if (gData_03003F60 & 0x80)
        {
            if ((gData_03000554->unk02 & 0x20) && gData_03000558->unk08 != NULL)
        {
            if (gData_03000558->unk34[1] >= 0)
            {
                pos = (s32 *)sub_0806DEF4((struct Unk6DEF4 *)sub_08062A14(), gData_03000558->unk34[1]);
                gData_03000554->unk04 = pos[0] >> 3;
                gData_03000554->unk06 = (pos[1] >> 3) - 16;
            }
            gData_03000198->unk17F6 = gData_03000558->unk08->unk01;
            gData_03000554->unk01 = 1;
            gData_03000554->unk00 = 1;
            sub_080435D8();
        }
        }
        else if (gData_03003F60 & 0x10)
        {
            if ((gData_03000554->unk02 & 0x40) && gData_03000558->unk0C != NULL)
        {
            if (gData_03000558->unk34[2] >= 0)
            {
                pos = (s32 *)sub_0806DEF4((struct Unk6DEF4 *)sub_08062A14(), gData_03000558->unk34[2]);
                gData_03000554->unk04 = pos[0] >> 3;
                gData_03000554->unk06 = (pos[1] >> 3) - 16;
            }
            gData_03000198->unk17F6 = gData_03000558->unk0C->unk01;
            gData_03000554->unk01 = 1;
            gData_03000554->unk00 = 2;
            sub_080435D8();
        }
        }
        else if (gData_03003F60 & 0x20)
        {
            if ((gData_03000554->unk02 & 0x80) && gData_03000558->unk10 != NULL)
        {
            if (gData_03000558->unk34[3] >= 0)
            {
                pos = (s32 *)sub_0806DEF4((struct Unk6DEF4 *)sub_08062A14(), gData_03000558->unk34[3]);
                gData_03000554->unk04 = pos[0] >> 3;
                gData_03000554->unk06 = (pos[1] >> 3) - 16;
            }
            gData_03000198->unk17F6 = gData_03000558->unk10->unk01;
            gData_03000554->unk01 = 1;
            gData_03000554->unk00 = 3;
            sub_080435D8();
        }
        }
        else if (gBtlKeysHeldU16 & 1)
        {
            if (gData_03000554->unk02 & 0x0F)
            {
                sub_08045AA8(&gData_03000198->unk18B8);
                gData_03000198->unk1833 = 1;
                gData_03000198->unk181C = 2;
                gData_03000554->unk01 = 0xFF;
                gData_03000198->unk1808 &= ~0x200;
                BtlClearUnk1834();
            }
        }
        if (gBtlKeysHeldU16 & 8)
        {
            sub_08066390(7);
            sub_0804109C((struct Unk40F4C *)&gData_03000198->unk0530, sub_0806639C());
            gData_03000198->unk181C = 3;
            sub_08060428();
        }
        break;
    case 1:
        sub_08043420();
        break;
    }
}
