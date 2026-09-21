/* match-flags: -fprologue-bugfix */
#include "global.h"
#include "ram_map.h"

// @ 0x0803dbd0
// 23/80 same-size. Retail is a leaf (`bx lr` only, no push) with the negative
// index handled by a FORWARD `blt` to a second block that falls through to the
// shared exit; -fprologue-bugfix is required to drop agbcc's `push {lr}`.
// Both paths redo the gMainWorkPtr->unk1818 lookup (not CSE'd in retail), so the
// two table expressions stay separate. Table bases must be distinct gData_*
// symbols or agbcc folds the second literal.
// Remaining DIFF: register choice / address-chain order in the a*40 path.
u32 sub_0803DBD0(u32 a)
{
    if ((s32)a < 0)
        return *(u32 *)(gData_08097458 + gMainWorkPtr->unk1818 * 4);
    return *(u32 *)(gData_080796DC + gMainWorkPtr->unk1818 * 4 + a * 40);
}
