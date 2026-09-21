#include "global.h"

// @ 0x080361a8
// 23/36 same-size (both compilers). Retail: movs r3,#0x0C; ldr r4,=0xFFFF;
// ldrh r1,[r0,#0x1C]; str r1,[r0,#0x1C]; ldr r2,[r0,#0x14]; subs/muls r1,r3;
// asrs r1,#8; str r1,[r0,#0x18]; adds r2,r2,r1; ands r2,r4; str r2,[r0,#0x14].
// The ldrh+str pair is a u16->u32 overlay at +0x1C, hence union Unk361A8Word.
// Remaining DIFF is a pure register rotation: agbcc gives scale->r2, mask->r3,
// value->r4, cur->r1; retail wants scale->r3, mask->r4, value->r1, cur->r2.
// All 24 declaration orders tried floor at 23/36 -> permuter.
// Role: Q8 one-pole smoothing of unk14 toward unk1C (12/256 per frame).
void sub_080361A8(struct Unk361A8 *a)
{
    s32 v = a->unk1C.h;
    s32 cur;
    u32 scale = 12;
    u32 mask = 0xFFFF;

    a->unk1C.w = v;
    cur = a->unk14;
    v = (s32)(v - cur);
    v = (s32)(v * scale) >> 8;
    a->unk18 = v;
    a->unk14 = (cur + v) & mask;
}
