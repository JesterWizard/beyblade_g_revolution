/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08033158
// 44/46 (95.7%), same size. Only DIFF: retail loop-exit is `cmp r1,#0; beq <movs r2,#1>`
// while agbcc merges the b==0 exit into the tail `r = b; if (b == 0) r = 1;` check,
// emitting `cmp r2,#0; beq <adds r2,r1,#0>`. Needs a source shape whose tail compare
// stays on b (r1) instead of the copied value.
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
        r = b;
        if (b == 0)
            r = 1;
        if (sign != 0)
            r = -r;
    }
    return r;
}
