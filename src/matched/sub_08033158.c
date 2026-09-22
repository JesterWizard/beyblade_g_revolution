/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08033158
// Sign-preserving normalise: |a| is shifted down to the top set bit of b, or
// becomes 1 when b is exhausted; the original sign is restored at the end.
// The `do { ... } while (0);` around `if (b) r = b;` is load-bearing: it gives
// that assignment its own basic block, so the loop-exit branch threads directly
// to `movs r2,#1` (retail) instead of landing on the `adds r2,r1,#0` that
// materialises `r = b`. Without the extra block the `beq` target is one
// instruction early and the function floors at 45/46.
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
        do
        {
            if (b)
                r = b;
        } while (0);
        if (b == 0)
            r = 1;
        if (sign != 0)
            r = -r;
    }
    return r;
}
