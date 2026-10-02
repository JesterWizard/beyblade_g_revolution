#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802bc14
/* A free CollectionEntry slot reads as the word 0xFF0000FF (unk00 = unk03 = 0xFF). */
s32 CollectionIsFull(s16 a)
{
    s32 count;
    s32 limit;
    s32 i;

    count = CollectionCountByKind((s8)a);
    limit = _0802BA7C((s8)a);
    DebugPrint((void *)0x0833BE30, (s16)a, count, limit);
    if (count < limit)
    {
        if (gMainWorkPtr->unk1694 != NULL)
        {
            for (i = 0; i <= 0x7F; i++)
            {
                if (((u32 *)gMainWorkPtr->unk1694)[i] == 0xFF0000FF)
                    return 0;
            }
        }
    }
    return 1;
}

