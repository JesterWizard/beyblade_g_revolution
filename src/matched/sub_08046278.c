#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08046278
// Reset both unk16B0 slots to {0, -1, -1} (unconditional form of BtlResetUnk16B0).
void BtlInitUnk16B0Slots(void)
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        gData_03000198->unk16B0[i].unk00 = 0;
        gData_03000198->unk16B0[i].unk04 = -1;
        gData_03000198->unk16B0[i].unk08 = -1;
    }
}

