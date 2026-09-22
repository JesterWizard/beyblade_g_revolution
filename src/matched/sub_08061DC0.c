#include "global.h"
#include "ram_map.h"

// @ 0x08061dc0
/* match-compiler: old_agbcc */
// Two VRAM addresses (common base + per-arg scaled offset) handed to the
// bx-r3 trampoline _08073C4C with the stride and a table entry.
// `a0 = lo + b0` must be materialised before `b1` is computed: retail serialises
// addr0 fully before it starts addr1, so the first `add lo` cannot be sunk.
void sub_08061DC0(u16 arg0, u16 arg1)
{
    s32 stride;
    s32 lo;
    u32 b0;
    u32 b1;
    void *a0;

    stride = (gUnk_03000798->unk98 >> 3) << 5;
    lo = gUnk_03000798->unk5D << 0xE;
    b0 = arg0 * stride + 0x06000000;
    a0 = (void *)(lo + b0);
    b1 = arg1 * stride + 0x06000000;
    _08073C4C(a0, (void *)(lo + b1), stride, *(void **)0x080BB8C0);
}
