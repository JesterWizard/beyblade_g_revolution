#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080731f4
/* match-compiler: old_agbcc */
s32 sub_080731F4(u8 *s)
{
    s32 n = 0;

    if (s == 0)
        return 0;
    while (*s != 0)
    {
        *s++ = 0;
        n++;
    }
    return n;
}

