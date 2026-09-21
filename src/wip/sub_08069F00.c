/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08069f00
// 11/24 same-size (45.8%). Retail: r1 = v (`adds r1,r0,#0`) then `cmp r0,#0;
// bge; adds r1,#0xFF` then `lsls r0,r1,#8; asrs r0,r0,#0x10`. agbcc adds 0xFF
// in place (r0) — it coalesces the copy of the multiply result with the result
// variable. Needs a source shape that keeps v in r0 and the adjusted value in r1.
// Role: (s16)a * (s16)b, rounded toward zero by 1/256 (Q8 fixed point).
s32 sub_08069F00(s16 a, s16 b)
{
    s32 v = a * b;
    s32 r = v;

    if (v < 0)
        r += 0xFF;
    return (r << 8) >> 16;
}
