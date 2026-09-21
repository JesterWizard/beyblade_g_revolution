/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08033158
// 45/46 same-size. Permuter candidate (nonmatchings/sub_08033158/output-0-1)
// fixed the tail compare register (retail `cmp r1,#0`, agbcc `cmp r2,#0`) via the
// `if (b || sign) r = b; else r = b;` shape. Remaining DIFF: the loop-exit `beq`
// target -- retail jumps straight to `movs r2,#1`, agbcc lands on `adds r2,r1,#0`
// first (semantically equivalent, one instruction longer path).
s32 sub_08033158(s32 a, s32 b)
{
    s32 r = a;
    u32 sign = (u32)r >> 31;

    if (r != 0)
    {
        if (sign != 0)
            r = -r;
        while (b != 0)
        {
            if (r > (b << 8))
                break;
            b >>= 1;
        }
        if (b || sign)
        {
            r = b;
        }
        else
        {
            r = b;
        }
        if (b == 0)
            r = 1;
        if (sign != 0)
            r = -r;
    }
    return r;
}
