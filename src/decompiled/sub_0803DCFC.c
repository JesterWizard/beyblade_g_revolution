/* match-compiler: old_agbcc */
#include "global.h"
#include "data_symbols.h"
#include "ram_map.h"

void *sub_0803DCFC(u32 a)
{
    u8 *base;
    u32 off;
    u32 index;

    index = a;
    if (index <= 0x52)
    {
        base = gData_0807A1F4;
        off = index * 40;
        return (void *)(base + off);
    }
    DebugPrint((void *)gData_0833D1E0, (void *)gData_0833D1F4);
    return 0;
}
