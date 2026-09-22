/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061800
// MATCHED -> src/matched/sub_08061800.c (old_agbcc)
// `off = arg0 * stride + 0x06000000` must be a separate local: retail forms
// `arg0*stride + 0x06000000` first and adds `lo` last, while left-associating
// the sum in one expression makes agbcc accumulate `lo + arg0*stride` first.
void sub_08061800(u16 arg0)
{
    struct Unk0798 *p = gUnk_03000798;
    s32 lo;
    u16 h;
    s32 stride;
    s32 off;

    if (arg0 >= (p->unk9A >> 3) - 1)
        return;

    lo = (s32)p->unk5D;
    lo <<= 0xE;
    h = p->unk98;
    stride = (h >> 3) << 5;
    off = arg0 * stride + 0x06000000;
    _08073C4C((void *)0, (void *)(lo + off), stride, *(void **)0x080BB8BC);
}
