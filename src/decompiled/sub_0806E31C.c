#include "global.h"

// @ 0x0806e31c
u32 sub_0806E31C(void *a, void *b, s32 *out, s32 d)
{
    u8 *node;
    u32 *tbl;
    u32 maxIdx;
    s32 idx;
    s32 frac;
    s32 *p0;
    s32 *p1;
    s32 t;

    node = sub_0806DEC8(a, (s32)b);
    tbl = (u32 *)(node + 0x20);
    if (d < 0)
        d = 0;
    idx = d >> 10;
    maxIdx = *(u32 *)node;
    if (idx >= (s32)maxIdx)
        d = ((maxIdx - 1) << 10) | (d & 0x3FF);
    idx = d >> 10;
    frac = d & 0x3FF;
    p0 = (s32 *)sub_0806DEF4(a, tbl[idx]);
    p1 = (s32 *)sub_0806DEF4(a, tbl[idx + 1]);
    t = p1[0] - p0[0];
    t = (t * frac) >> 10;
    out[0] = p0[0] + t;
    t = p1[1] - p0[1];
    t = (t * frac) >> 10;
    out[1] = p0[1] + t;
    t = p1[2] - p0[2];
    t = (t * frac) >> 10;
    out[2] = p0[2] + t;
    out[3] = frac;
    out[4] = idx;
    return (u32)out;
}
