#include "global.h"

/*
 * WIP — not byte-matched (best clean rewrite was 92/108 bytes).
 * Retail uses an explicit `>` table-call path followed by a separate
 * `<` zero-call comparison; straightforward C reproduces the logic but
 * still produces a different literal-pool/register layout in this build.
 *
 * This function is the asm-wrapper style micro-`if/else-if` idiom seen
 * near the "systemic agbcc leaf-function register-allocation quirk"
 * dead-end list; likely needs a permuter run targeting instruction-order/
 * dead-code retention rather than hand-C changes.
 *
 * Table lookup notes (verified correct, safe to reuse):
 *   table = ((s8 **)0x0807741C)[gMainWorkPtr->unk15C8];
 *   table += (s32)gMainWorkPtr->unk15CA * 16;
 *   compares gMainWorkPtr->unk15D0 vs ->unk15D2 (s16)
 *   calls _0802D058((u16)table[1]) or _0802D058(0)
 * @ 0x0802d2c0
 */
void sub_0802D2C0(void)
{
    s8 *table;
    struct MainWork *w1;
    struct MainWork *w2;

    w1 = gMainWorkPtr;
    table = ((s8 **)0x0807741C)[w1->unk15C8];
    w2 = gMainWorkPtr;
    table += (s32)w2->unk15CA * 16;

    if (gMainWorkPtr->unk15D0 > gMainWorkPtr->unk15D2)
        _0802D058((u16)table[1]);
    else if (gMainWorkPtr->unk15D0 < gMainWorkPtr->unk15D2)
        _0802D058(0);
}
