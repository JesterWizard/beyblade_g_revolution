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
        if ((s8)gMainWorkPtr->unk1694[i].kind == (s16)a && (s8)gMainWorkPtr->unk1694[i].group == (s8)b)
        {
            gMainWorkPtr->unk1694[i].kind |= 0xFF;
            gMainWorkPtr->unk1694[i].group |= 0xFF;
            gMainWorkPtr->unk1694[i].value = 0;
            gMainWorkPtr->unk1694[i].slot = 0;
            return;
        }
    }
}

