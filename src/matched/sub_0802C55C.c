#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802c55c
/* match-compiler: old_agbcc */
// Free slot `i` of the MainWork.unk1694 table if it holds (a, b); a freed
// kind-1 slot also notifies sub_0803E0CC.
void sub_0802C55C(u16 a, u8 b, s16 i)
{
    s8 kind;

    if (i > 0x7F)
        return;
    if ((s8)gMainWorkPtr->unk1694[i].unk00 != (s16)a)
        return;
    kind = (s8)gMainWorkPtr->unk1694[i].unk03;
    if (kind != (s8)b)
        return;
    gMainWorkPtr->unk1694[i].unk00 |= 0xFF;
    gMainWorkPtr->unk1694[i].unk03 |= 0xFF;
    gMainWorkPtr->unk1694[i].unk02 = 0;
    gMainWorkPtr->unk1694[i].unk01 = 0;
    if (kind == 1)
        RemoveBladeFromTysonsCollection(i);
}

