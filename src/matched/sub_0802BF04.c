#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802bf04
/* match-compiler: old_agbcc */
// Free the first MainWork.unk1694 slot holding (a, b).
void sub_0802BF04(u16 a, u8 b)
{
    s32 i;

    if (gMainWorkPtr->unk1694 == NULL)
        return;
    for (i = 0; i <= 0x7F; i++)
    {
        if ((s8)gMainWorkPtr->unk1694[i].unk00 == (s16)a && (s8)gMainWorkPtr->unk1694[i].unk03 == (s8)b)
        {
            gMainWorkPtr->unk1694[i].unk00 |= 0xFF;
            gMainWorkPtr->unk1694[i].unk03 |= 0xFF;
            gMainWorkPtr->unk1694[i].unk02 = 0;
            gMainWorkPtr->unk1694[i].unk01 = 0;
            return;
        }
    }
}

