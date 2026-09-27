/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void sub_080436B0(void)
{
    u8 phase;
    s32 *pos;
    struct Unk0554 *st;

    phase = gUnk_03000554->unk01;
    if (phase == 0)
    {
        if (*(u16 *)gBtlInputMask & 0x40)
        {
            if ((gUnk_03000554->unk02 & 0x10) && gUnk_03000558->unk04 != NULL)
        {
            if (gUnk_03000558->unk34[0] >= 0)
            {
                pos = (s32 *)sub_0806DEF4((struct Unk6DEF4 *)sub_08062A14(), gUnk_03000558->unk34[0]);
                st = gUnk_03000554;
                st->unk04 = pos[0] >> 3;
                st->unk06 = (pos[1] >> 3) - 16;
            }
            gMainWorkPtr->unk17F6 = gUnk_03000558->unk04->unk01;
            gUnk_03000554->unk01 = 1;
            gUnk_03000554->unk00 = phase;
            sub_080435D8();
        }
        }
        else if (*(u16 *)gBtlInputMask & 0x80)
        {
            if ((gUnk_03000554->unk02 & 0x20) && gUnk_03000558->unk08 != NULL)
        {
            if (gUnk_03000558->unk34[1] >= 0)
            {
                pos = (s32 *)sub_0806DEF4((struct Unk6DEF4 *)sub_08062A14(), gUnk_03000558->unk34[1]);
                st = gUnk_03000554;
                st->unk04 = pos[0] >> 3;
                st->unk06 = (pos[1] >> 3) - 16;
            }
            gMainWorkPtr->unk17F6 = gUnk_03000558->unk08->unk01;
            gUnk_03000554->unk01 = 1;
            gUnk_03000554->unk00 = 1;
            sub_080435D8();
        }
        }
        else if (*(u16 *)gBtlInputMask & 0x10)
        {
            if ((gUnk_03000554->unk02 & 0x40) && gUnk_03000558->unk0C != NULL)
        {
            if (gUnk_03000558->unk34[2] >= 0)
            {
                pos = (s32 *)sub_0806DEF4((struct Unk6DEF4 *)sub_08062A14(), gUnk_03000558->unk34[2]);
                st = gUnk_03000554;
                st->unk04 = pos[0] >> 3;
                st->unk06 = (pos[1] >> 3) - 16;
            }
            gMainWorkPtr->unk17F6 = gUnk_03000558->unk0C->unk01;
            gUnk_03000554->unk01 = 1;
            gUnk_03000554->unk00 = 2;
            sub_080435D8();
        }
        }
        else if (*(u16 *)gBtlInputMask & 0x20)
        {
            if ((gUnk_03000554->unk02 & 0x80) && gUnk_03000558->unk10 != NULL)
        {
            if (gUnk_03000558->unk34[3] >= 0)
            {
                pos = (s32 *)sub_0806DEF4((struct Unk6DEF4 *)sub_08062A14(), gUnk_03000558->unk34[3]);
                st = gUnk_03000554;
                st->unk04 = pos[0] >> 3;
                st->unk06 = (pos[1] >> 3) - 16;
            }
            gMainWorkPtr->unk17F6 = gUnk_03000558->unk10->unk01;
            gUnk_03000554->unk01 = 1;
            gUnk_03000554->unk00 = 3;
            sub_080435D8();
        }
        }
        else if (gBtlKeysHeldU16 & 1)
        {
            if (gUnk_03000554->unk02 & 0x0F)
            {
                sub_08045AA8(&gMainWorkPtr->unk18B8);
                gMainWorkPtr->unk1833 = 1;
                gMainWorkPtr->unk181C = 2;
                gUnk_03000554->unk01 = 0xFF;
                gMainWorkPtr->unk1808 &= ~0x200;
                BtlClearUnk1834();
            }
        }
        if (gBtlKeysHeldU16 & 8)
        {
            sub_08066390(7);
            sub_0804109C((struct Unk40F4C *)&gMainWorkPtr->unk0530, sub_0806639C());
            gMainWorkPtr->unk181C = 3;
            sub_08060428();
        }
    }
    else if (phase == 1)
    {
        sub_08043420();
    }
}
