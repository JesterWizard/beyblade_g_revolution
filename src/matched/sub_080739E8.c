#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080739e8
/* match-compiler: old_agbcc */
// TRUE if the string contains '\n'. A NULL string falls off the end without a
// return (retail bug): r0 still holds the NULL argument, so it returns 0.
s32 TextHasNewline(u8 *s)
{
    u8 c;
    u32 i;

    if (s != NULL)
    {
        c = s[0];
        i = 1;
        while (c != 0)
        {
            if (c == '\n')
                return 1;
            c = s[i++];
        }
        return 0;
    }
}

