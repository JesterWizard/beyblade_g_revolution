/* match-compiler: old_agbcc */
#include "global.h"
#include "data_symbols.h"
#include "ram_map.h"

// @ 0x0803dcfc
// 44/48 same_size: index lands in r1 (retail r2). pin_pool_live gets r2 + perfect
// ok-path but inserts early ldr before cmp. Permuter best valid 44/48.
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
