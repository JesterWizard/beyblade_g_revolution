#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802c314
/* match-compiler: old_agbcc */

s32 sub_0802C314(s8 a, u8 b, struct CollectionLookup *out)
{
    s32 i;

    if (out != NULL)
    {
        out->index = -1;
        out->kind |= 0xFF;
        out->group |= 0xFF;
        out->value = 0;
        out->slot = 0;
        out->entry = NULL;
    }
    if (gMainWorkPtr->unk1694 != NULL)
    {
        for (i = 0; i <= 0x7F; i++)
        {
            if ((s8)gMainWorkPtr->unk1694[i].group == a && gMainWorkPtr->unk1694[i].slot == (s8)b)
            {
                if (out != NULL)
                {
                    out->index = i;
                    out->kind = gMainWorkPtr->unk1694[i].kind;
                    out->group = gMainWorkPtr->unk1694[i].group;
                    out->value = gMainWorkPtr->unk1694[i].value;
                    out->slot = gMainWorkPtr->unk1694[i].slot;
                    out->entry = &gMainWorkPtr->unk1694[i];
                }
                return 1;
            }
        }
    }
    return 0;
}

