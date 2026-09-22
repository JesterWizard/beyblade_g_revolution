/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08061dc0
// Two VRAM addresses from a common base plus a per-arg scaled offset, handed to
// the bx-r3 trampoline _08073C4C with the stride and a table entry.
// 66/72 same-size: only the ordering of the two `add lo` steps differs (retail
// serialises addr0 before computing addr1; agbcc sinks both lo-adds to the end).
void sub_08061DC0(u16 arg0, u16 arg1)
{
    s32 stride;
    s32 lo;
    u32 b0;
    u32 b1;

    stride = (gUnk_03000798->unk98 >> 3) << 5;
    lo = gUnk_03000798->unk5D << 0xE;
    b0 = arg0 * stride + 0x06000000;
    b1 = arg1 * stride + 0x06000000;
    _08073C4C((void *)(lo + b0), (void *)(lo + b1), stride, *(void **)0x080BB8C0);
}
