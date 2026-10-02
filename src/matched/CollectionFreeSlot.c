#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802c55c
/* match-compiler: old_agbcc */
// Free slot `i` of the MainWork.unk1694 table if it holds (a, b); a freed
// kind-1 slot also notifies sub_0803E0CC.
void CollectionFreeSlot(u16 a, u8 b, s16 i)
{
    s8 kind;

    if (i > 0x7F)
        return;
    if ((s8)gMainWorkPtr->unk1694[i].kind != (s16)a)
        return;
    kind = (s8)gMainWorkPtr->unk1694[i].group;
    if (kind != (s8)b)
        return;
    gMainWorkPtr->unk1694[i].kind |= 0xFF;
    gMainWorkPtr->unk1694[i].group |= 0xFF;
    gMainWorkPtr->unk1694[i].value = 0;
    gMainWorkPtr->unk1694[i].slot = 0;
    if (kind == 1)
        RemoveBladeFromTysonsCollection(i);
}

