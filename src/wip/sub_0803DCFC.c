#include "global.h"
#include "data_symbols.h"

// @ 0x0803dcfc
// 44/48 same-size. Only DIFF: retail copies the index to r2 (`adds r2,r0,#0`)
// and the multiply path uses r2; agbcc keeps it in r1. Distinct gData_* table
// symbols are required (0x0833D1E0 / 0x0833D1F4 differ by 0x14 and get folded).
// Role: index into the 40-byte-stride table at 0x0807A1F4, or log+return 0
// when the index is out of range (> 0x52).
void *sub_0803DCFC(u32 a)
{
    u32 idx = a;

    if (idx <= 0x52)
        return (void *)(gData_0807A1F4 + idx * 40);
    sub_08067B98((void *)gData_0833D1E0, (void *)gData_0833D1F4);
    return 0;
}
