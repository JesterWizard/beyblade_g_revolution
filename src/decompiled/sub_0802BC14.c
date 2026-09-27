#include "global.h"
#include "ram_map.h"

s32 sub_0802BC14(u16 a)
{
    s32 count;
    s32 limit;
    u32 *slot;
    s32 i;

    count = sub_0802C62C((s8)a);
    limit = _0802BA7C((s8)a);
    DebugPrint((void *)0x0833BE30, (s16)a, count, limit);
    if (count < limit)
    {
        slot = (u32 *)gMainWorkPtr->unk1694;
        if (slot != NULL)
        {
            for (i = 0; i <= 0x7F; i++)
            {
                if (slot[i] == 0xFF0000FF)
                    return 0;
            }
        }
    }
    return 1;
}
