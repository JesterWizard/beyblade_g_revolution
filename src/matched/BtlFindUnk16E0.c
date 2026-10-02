#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08043b90
/* match-compiler: old_agbcc */
// Walk MainWork.unk16E0 ({ptr,s32} records) until sub_08073440(entry->unk00,
// unk16C8) returns 0, then return entry->unk04. Null list -> -1.
s32 BtlFindUnk16E0(void)
{
    struct Unk16E0 *node = gMainWorkPtr->unk16E0;

    if (node == 0)
        return -1;
    while (node->unk00 != 0)
    {
        if (StringCompare(node->unk00, gMainWorkPtr->unk16C8) == 0)
            return node->unk04;
        node++;
    }
    // BUG: no return when the list is exhausted; r0 still holds the 0 from
    // the loop test, so callers see 0.
#ifdef BUGFIX
    return 0;
#endif
}

