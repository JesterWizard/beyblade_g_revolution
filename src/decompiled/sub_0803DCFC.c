/* match-compiler: old_agbcc */
#include "global.h"
#include "data_symbols.h"
#include "ram_map.h"

// @ 0x0803DCFC
// 40-byte stride table lookup at gData_0807A1F4, or debug+NULL when index > 0x52.
void *sub_0803DCFC(u32 a)
{
    u32 index;

    index = a;
    if (index <= 0x52)
        return (void *)(gData_0807A1F4 + index * 40);
    DebugPrint((void *)gData_0833D1E0, (void *)gData_0833D1F4);
    return 0;
}
