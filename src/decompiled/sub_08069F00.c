/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08069f00
// 11/24 same-size (old_agbcc; plain agbcc is 6 bytes larger). Q8 multiply with
// floor rounding: p = a*b; if (p < 0) p += 0xFF; return (p << 8) >> 16.
// Retail: muls r0,r1; adds r1,r0,#0; cmp r0,#0; bge; adds r1,#0xFF; lsls r0,r1,#8;
// asrs r0,r0,#0x10. The only missing piece is that `adds r1,r0,#0` copy: agbcc
// coalesces the two locals (r and p) and emits `cmp r0,#0 / adds r0,#0xFF` plus a
// trailing nop, because after the copy `p` is only read by the compare. Tried:
// `s32 r = p; if (p<0) r += 0xFF`, `r = p;` as a statement, ternary
// `r = (p<0) ? p + 0xFF : p`, if/else assigning r in both arms, `(s16)(p << 8)`,
// `(p << 8) >> 16` -- all 11/24. Needs a source shape where the copy survives the
// allocator, or a permuter pass.
s32 sub_08069F00(s16 a, s16 b)
{
    s32 p = (s32)a * b;
    s32 r = p;

    if (p < 0)
        r += 0xFF;
    return (r << 8) >> 16;
}
