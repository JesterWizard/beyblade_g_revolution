#include "global.h"
#include "ram_map.h"

// Debounce gBtlInputMask. 0xFC00 clears the hold; otherwise unk1778
// counts down before the current mask is accepted.
u32 sub_08045C5C(u32 a, u32 b)
{
    if ((*(volatile u16 *)&gData_03003F60) == 0xFC00)
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
    if (gData_03000198->unk1774 == (*(volatile u16 *)&gData_03003F60))
        gData_03000198->unk1778 = b;
    else
        gData_03000198->unk1778 = a;
    gData_03000198->unk1774 = (*(volatile u16 *)&gData_03003F60);
    return (*(volatile u16 *)&gData_03003F60);
}
