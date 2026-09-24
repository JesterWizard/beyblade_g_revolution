/* match-flags: -fprologue-bugfix */
#include "global.h"

// @ 0x080739e8
// Best agbcc: 35/36 (97.2%). Null-path beq offset 0c vs retail 0d (1 byte).
// Dead tail required for loop body; without it score drops to 9/36.
// old_agbcc (no -fprologue-bugfix) can fix the beq (0d) with out/goto/finish
// shape but regresses to 32/36 (+4B epilogue, newline uses r2 not r0).
s32 sub_080739E8(u8 *s)
{
    u8 c;
    u32 i;

    if (s == 0)
        return 0;

    c = s[0];
    i = 1;
    if (c == 0)
        return 0;

    while (c != 0)
    {
        if (c == 0x0A)
            return 1;
        c = s[i];
        i++;
    }

    if (s)
        return 0;
    else
        return 0;
}
