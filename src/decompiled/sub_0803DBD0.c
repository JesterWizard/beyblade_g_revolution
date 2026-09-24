/* match-flags: -fprologue-bugfix */
#include "global.h"
#include "ram_map.h"

// @ 0x0803dbd0
u32 sub_0803DBD0(u32 a)
{
    if ((s32)a < 0)
        return *(u32 *)(gData_08097458 + gMainWorkPtr->unk1818 * 4);
    return *(u32 *)(gData_080796DC + gMainWorkPtr->unk1818 * 4 + a * 40);
}
