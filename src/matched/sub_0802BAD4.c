#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802bad4
// This caller was built against an older (s8, s8, u8) prototype of
// sub_0803DEC8; its definition takes (u16, u8, u8).
#define BeybladeRecordClaimS8(a, b, c) ((void (*)(s8, s8, u8))sub_0803DEC8)(a, b, c)

// Claims the first free Unk1694 slot (word 0xFF0000FF) for (kind, group, c, d),
// if the group still has room. Group 1 first registers the entry through
// sub_0802C3DC/sub_0803DEC8 (logging and skipping the slot on failure). Retail
// has a separate copy of the slot writes in each branch. Returns 1 once a free
// slot was found, else 0.
s32 sub_0802BAD4(u8 kind, u8 group, u8 c, u8 d)
{
    s32 i;
    s32 err;

    if (gMainWorkPtr->unk1694 == NULL)
        return 0;
    if (sub_0802C62C(group) >= _0802BA7C(group))
        return 0;
    for (i = 0; i <= 0x7F; i++)
    {
        if (((u32 *)gMainWorkPtr->unk1694)[i] == 0xFF0000FF)
        {
            if ((s8)group == 1)
            {
                err = sub_0802C3DC(1, kind, NULL);
                if (err == 0)
                {
                    BeybladeRecordClaimS8(kind, d, i);
                    gMainWorkPtr->unk1694[i].unk02 = err;
                    gMainWorkPtr->unk1694[i].unk00 = kind;
                    gMainWorkPtr->unk1694[i].unk03 = group;
                    gMainWorkPtr->unk1694[i].unk01 = c;
                    gMainWorkPtr->unk1694[i].unk02 = d;
                }
                else
                    DebugPrint((void *)0x0833BE1C, (s8)kind);
            }
            else
            {
                gMainWorkPtr->unk1694[i].unk00 = kind;
                gMainWorkPtr->unk1694[i].unk03 = group;
                gMainWorkPtr->unk1694[i].unk01 = c;
                gMainWorkPtr->unk1694[i].unk02 = d;
            }
            return 1;
        }
    }
    return 0;
}

