/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08033158
// 45/46 same-size, one word off. Sign-preserving normalise: |a| is shifted down
// to the top set bit of b, or 1 when b is exhausted.
// Remaining DIFF is 0x14 only: the loop-exit `beq` target. Retail jumps
// straight to `movs r2,#1` (`05d0`), agbcc lands on the `adds r2,r1,#0` that
// materialises `r = b` (`02d0`) and falls through. Same size and semantics;
// jump-threading difference, so `if (b) r = b;` scores the target correctly but
// coalesces r into b and then emits `cmp r2,#0` instead of retail's `cmp r1,#0`
// (that coalesced shape is the 45/46 seed below; plain `r = b;` scores 44/46).
// Permuter candidate (chain, 97.8%).
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
        if (b)
            r = b;
        if (b == 0)
            r = 1;
        if (sign != 0)
            r = -r;
    }
    return r;
}
