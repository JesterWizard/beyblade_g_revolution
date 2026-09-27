#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802c314
/* match-compiler: old_agbcc */

s32 sub_0802C314(s8 a, u8 b, struct Unk2C314 *out)
{
    s32 i;

    if (out != NULL)
    {
        out->unk04 = -1;
        out->unk00 |= 0xFF;
        out->unk03 |= 0xFF;
        out->unk02 = 0;
        out->unk01 = 0;
        out->unk08 = NULL;
    }
    if (gMainWorkPtr->unk1694 != NULL)
    {
        for (i = 0; i <= 0x7F; i++)
        {
            if ((s8)gMainWorkPtr->unk1694[i].unk03 == a && gMainWorkPtr->unk1694[i].unk01 == (s8)b)
            {
                if (out != NULL)
                {
                    out->unk04 = i;
                    out->unk00 = gMainWorkPtr->unk1694[i].unk00;
                    out->unk03 = gMainWorkPtr->unk1694[i].unk03;
                    out->unk02 = gMainWorkPtr->unk1694[i].unk02;
                    out->unk01 = gMainWorkPtr->unk1694[i].unk01;
                    out->unk08 = &gMainWorkPtr->unk1694[i];
                }
                return 1;
            }
        }
    }
    return 0;
}

