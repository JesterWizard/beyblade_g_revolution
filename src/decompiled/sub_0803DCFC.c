#include "global.h"
#include "data_symbols.h"

// @ 0x0803dcfc
// 44/48 same-size. Only DIFF: retail keeps the index in r2 (`adds r2,r0,#0`)
// where agbcc picks r1. Distinct gData_* table symbols are required
// (0x0833D1E0 / 0x0833D1F4 differ by 0x14 and would be folded).
// Role: index into the 40-byte-stride table at 0x0807A1F4, or log+return 0
// when the index is out of range (> 0x52).
void *sub_0803DCFC(u32 a)
{
    if (a <= 0x52)
        return (void *)(gData_0807A1F4 + a * 40);
    DebugPrint((void *)gData_0833D1E0, (void *)gData_0833D1F4);
    return 0;
}
