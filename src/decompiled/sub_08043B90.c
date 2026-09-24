#include "global.h"

// @ 0x08043b90
// Walk MainWork.unk16E0 ({ptr,s32} records) until sub_08073440(entry->unk00,
// unk16C8) returns 0, then return entry->unk04. Null list -> -1, no match -> 0.
//
// 67/76 near-miss: retail loop exit falls through with r0 already 0 from the
// head test (ldr/cmp/bne); agbcc emits `movs r0,#0` before pop for `return 0`.
// `return (s32)node->unk00` reloads; `while ((key=...)!=0) return (s32)key`
// bloats to 80B. Do not use gMainWorkPtr symbols here (14/76). Permuter
// randomization regresses this seed (best score 200).
s32 sub_08043B90(void)
{
    struct Unk16E0 *node = gMainWorkPtr->unk16E0;

    if (node == 0)
        return -1;
    while (node->unk00 != 0)
    {
        if (sub_08073440(node->unk00, gMainWorkPtr->unk16C8) == 0)
            return node->unk04;
        node++;
    }
    return 0;
}
