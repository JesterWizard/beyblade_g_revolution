#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08056f84
// Look up the current 16E0 entry; if its slot is free, start mode 2 and load
// the linked record (id -> unk17E4, optional follow-up script).
void sub_08056F84(void)
{
    s32 index;
    u32 result;
    u32 busy;
    struct Unk2B95C *entry;

    index = BtlFindUnk16E0();
    if (index < 0)
        return;
    EventFlagOp((u8)index, 4, &result);
    busy = result;
    if (busy != 0)
    {
        gMainWorkPtr->unk17FC = 1;
        return;
    }
    sub_0802D52C(2, 1);
    gMainWorkPtr->unk181D = 2;
    gMainWorkPtr->unk17FC = busy;
    entry = FindEntryByString(gMainWorkPtr->unk16C8);
    if (entry != 0)
    {
        gMainWorkPtr->unk17E4 = entry->unk00;
        if (entry->unk08 != 0)
            ScriptRun(0, entry->unk08);
    }
    else
        gMainWorkPtr->unk17E4 = 0xFFFF;
}

