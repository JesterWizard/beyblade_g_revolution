#include "global.h"

/*
 * WIP — not byte-matched (49.1%, 53/108 bytes originally; best clean
 * rewrite compiled to 92/108, i.e. agbcc dead-code-eliminates the
 * `else if (a->unk15D0 < a->unk15D2)` branch since it's unreachable given
 * the preceding `if (<=)`. Retail keeps a genuinely dead
 * `cmp r2,r0; bge end; movs r0,#0; bl _0802D058` block (108 bytes) that no
 * straightforward C source reproduces — agbcc always optimizes the
 * redundant re-check away in this build (92 bytes, correct semantics,
 * but short by exactly the dead block).
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

    if (gMainWorkPtr->unk15D0 <= gMainWorkPtr->unk15D2)
        _0802D058((u16)table[1]);
    else if (gMainWorkPtr->unk15D0 < gMainWorkPtr->unk15D2)
        _0802D058(0);
}
