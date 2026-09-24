/* match-compiler: old_agbcc */
#include "global.h"
#include "data_symbols.h"
#include "ram_map.h"

void *sub_0803DCFC(u32 a)
{
    u32 index;
    u32 off;
    u8 *base;

    index = a;
    if (index <= 0x52)
    {
        off = index << 2;
        off += index;
        off <<= 3;
        base = gData_0807A1F4;
        return (void *)(base + off);
    }
    DebugPrint((void *)gData_0833D1E0, (void *)gData_0833D1F4);
    return 0;
}
