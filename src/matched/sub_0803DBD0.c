#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803dbd0
/* match-flags: -fprologue-bugfix */

u32 sub_0803DBD0(u32 a)
{
    u8 *table;
    u32 offset;
    u32 *fallback;
    u32 value;
    s32 row = a;

    if (row >= 0)
    {
        table = gData_080796DC;
        value = gMainWorkPtr->language;
        offset = value * 4 + row * 40;
        value = *(u32 *)(table + offset);
    }
    else
    {
        fallback = (u32 *)gData_08097458;
        value = fallback[gMainWorkPtr->language];
    }
    return value;
}

