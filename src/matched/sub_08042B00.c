#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042b00
void *sub_08042B00(u32 i)
{
    u32 **tbl = (u32 **)gData_08090FF0;
    u8 *p = (u8 *)gData_03000198[0];

    return (void *)tbl[*(u8 *)(p + 0x1818)][i];
}

