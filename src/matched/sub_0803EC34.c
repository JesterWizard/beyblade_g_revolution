#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803ec34
#include "global.h"

// @ 0x0803ec34
u32 sub_0803EC34(u32 i)
{
    u32 **tbl = (u32 **)gData_0807BB6C;
    u8 *p = (u8 *)gData_03000198[0];

    return tbl[*(u8 *)(p + 0x1818)][i];
}

