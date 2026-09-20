#include "global.h"

void sub_080436B0(void)
{
    struct Unk0554 **stateLoc;
    u8 phase;
    u16 input;

    stateLoc = (struct Unk0554 **)0x03000554;
    phase = (*stateLoc)->unk01;
    if (phase == 0)
    {
        input = *(vu16 *)gBtlInputMask;
        if ((input & 0x40) != 0)
        {
            struct Unk436B0Entry *entry;
            struct Unk6DEF4 *lookup;
            s32 *coords;

            if (((*stateLoc)->unk02 & 0x10) == 0)
                goto common;
            entry = gUnk_03000558->unk04;
            if (entry == 0)
                goto common;
            if (entry->unk34 >= 0)
            {
                lookup = (struct Unk6DEF4 *)sub_08062A14();
                lookup = (struct Unk6DEF4 *)sub_0806DEF4(
                    lookup,
                    entry->unk34);
                coords = (s32 *)lookup;
                (*stateLoc)->unk04 = coords[0] >> 3;
                (*stateLoc)->unk06 = (coords[1] >> 3) - 0x10;
            }
            gMainWorkPtr->unk17F6 = entry->unk01;
            (*stateLoc)->unk01 = 1;
            (*stateLoc)->unk00 = phase;
            sub_080435D8();
            goto common;
        }
        if ((input & 0x80) != 0)
        {
            struct Unk436B0Entry *entry;
            struct Unk6DEF4 *lookup;
            s32 *coords;

            if (((*stateLoc)->unk02 & 0x20) == 0)
                goto common;
            entry = gUnk_03000558->unk08;
            if (entry == 0)
                goto common;
            if (entry->unk36 >= 0)
            {
                lookup = (struct Unk6DEF4 *)sub_08062A14();
                lookup = (struct Unk6DEF4 *)sub_0806DEF4(
                    lookup,
                    entry->unk36);
                coords = (s32 *)lookup;
                (*stateLoc)->unk04 = coords[0] >> 3;
                (*stateLoc)->unk06 = (coords[1] >> 3) - 0x10;
            }
            gMainWorkPtr->unk17F6 = entry->unk01;
            (*stateLoc)->unk01 = 1;
            (*stateLoc)->unk00 = 1;
            sub_080435D8();
            goto common;
        }
        if ((input & 0x10) != 0)
        {
            struct Unk436B0Entry *entry;
            struct Unk6DEF4 *lookup;
            s32 *coords;

            if (((*stateLoc)->unk02 & 0x40) == 0)
                goto common;
            entry = gUnk_03000558->unk0C;
            if (entry == 0)
                goto common;
            if (entry->unk38 >= 0)
            {
                lookup = (struct Unk6DEF4 *)sub_08062A14();
                lookup = (struct Unk6DEF4 *)sub_0806DEF4(
                    lookup,
                    entry->unk38);
                coords = (s32 *)lookup;
                (*stateLoc)->unk04 = coords[0] >> 3;
                (*stateLoc)->unk06 = (coords[1] >> 3) - 0x10;
            }
            gMainWorkPtr->unk17F6 = entry->unk01;
            (*stateLoc)->unk01 = 1;
            (*stateLoc)->unk00 = 2;
            sub_080435D8();
            goto common;
        }
        if ((input & 0x20) != 0)
        {
            struct Unk436B0Entry *entry;
            struct Unk6DEF4 *lookup;
            s32 *coords;

            if (((*stateLoc)->unk02 & 0x80) == 0)
                goto common;
            entry = gUnk_03000558->unk10;
            if (entry == 0)
                goto common;
            if (entry->unk3A >= 0)
            {
                lookup = (struct Unk6DEF4 *)sub_08062A14();
                lookup = (struct Unk6DEF4 *)sub_0806DEF4(
                    lookup,
                    entry->unk3A);
                coords = (s32 *)lookup;
                (*stateLoc)->unk04 = coords[0] >> 3;
                (*stateLoc)->unk06 = (coords[1] >> 3) - 0x10;
            }
            gMainWorkPtr->unk17F6 = entry->unk01;
            (*stateLoc)->unk01 = 1;
            (*stateLoc)->unk00 = 3;
            sub_080435D8();
            goto common;
        }
        if ((*(vu16 *)gBtlKeysHeld & 1) != 0 &&
            ((*stateLoc)->unk02 & 0x0F) != 0)
        {
            sub_08045AA8(&gMainWorkPtr->unk18B8);
            gMainWorkPtr->unk1833 = 1;
            gMainWorkPtr->unk181C = 2;
            (*stateLoc)->unk01 = 0xFF;
            gMainWorkPtr->unk1808 &= ~0x200;
            sub_080433F4();
        }
    }
    else if (phase == 1)
    {
        sub_08043420();
        return;
    }
    else
    {
        return;
    }

common:
    if ((*(vu16 *)gBtlKeysHeld & 8) != 0 &&
        ((*stateLoc)->unk02 & 0x0F) != 0)
    {
        sub_08066390(7);
        sub_0804109C(&gMainWorkPtr->unk0530, sub_0806639C());
        gMainWorkPtr->unk181C = 3;
        sub_08060428();
    }
}
