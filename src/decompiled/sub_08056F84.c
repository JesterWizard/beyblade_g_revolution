#include "global.h"

void sub_08056F84(void)
{
    s32 index;
    u32 result;
    struct Unk2B95C *entry;
    struct MainWork **main_loc;

    index = BtlFindUnk16E0();
    if (index < 0)
        return;
    sub_08045D3C((u8)index, 4, &result);
    if (result != 0)
    {
        gMainWorkPtr->unk17FC = 1;
        return;
    }

    sub_0802D52C(2, 1);
    main_loc = gMainWorkPtrLoc;
    (*main_loc)->unk181D = 2;
    (*main_loc)->unk17FC = result;
    entry = (struct Unk2B95C *)sub_0802B95C((*main_loc)->unk16C8);
    if (entry == 0)
    {
        (*main_loc)->unk17E4 = 0xFFFF;
        return;
    }
    (*main_loc)->unk17E4 = entry->unk00;
    if (entry->unk08 != 0)
        sub_08059DC8(0, entry->unk08);
}
