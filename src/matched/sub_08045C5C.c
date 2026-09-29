#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08045c5c
/* match-compiler: old_agbcc */
// Debounce gBtlInputMask. 0xFC00 clears the hold; otherwise unk1778
// counts down before the current mask is accepted.
u32 sub_08045C5C(u32 a, u32 b)
{
    if (gData_03003F60 == 0xFC00)
    {
        gData_03000198->unk1778 = 0;
        gData_03000198->unk1774 = 0;
        return 0;
    }
    if (gData_03000198->unk1778 != 0)
    {
        gData_03000198->unk1778--;
        return 0;
    }
    if (gData_03000198->unk1774 == gData_03003F60)
        gData_03000198->unk1778 = b;
    else
        gData_03000198->unk1778 = a;
    gData_03000198->unk1774 = gData_03003F60;
    return gData_03003F60;
}

