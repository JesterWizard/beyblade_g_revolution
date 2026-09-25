/* match-flags: -fprologue-bugfix */
#include "global.h"

// @ 0x080739e8
// 35/36: sole DIFF is null-check beq target (0cd0→0dd0). Null must share the
// return-1 `bx lr` (r0 already 0) while empty/loop use `movs r0,#0`. Fallthrough
// `s=0; return s` gets 0dd0 but swaps r1/r2 (30/36).
s32 sub_080739E8(u8 *s)
{
    u8 *orig;
    u8 c;
    u32 i;

    orig = s;
    if (orig != 0)
    {
        c = orig[0];
        i = 1;
        while (c != 0)
        {
            if (c == 0x0A)
                return 1;
            c = orig[i];
            i++;
        }
        return 0;
    }
    return (s32)s;
}
