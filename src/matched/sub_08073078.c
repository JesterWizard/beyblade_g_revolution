#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08073078
/* match-compiler: old_agbcc */
s32 sub_08073078(u8 *s)
{
    s32 n = 0;

    if (s == 0)
        return -1;
    while (s[n] != 0)
        n++;
    return n;
}

