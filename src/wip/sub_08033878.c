#include "global.h"

// @ 0x08033878
void sub_08033878(void)
{
    s32 i;

    gBattleWork->unk0B64 = 0;
    gBattleWork->unk0B68 = 0;
    gBattleWork->unk0B6C = 0;
    gBattleWork->unk0B78 = 0;

    for (i = 0; i <= 3; i++)
    {
        if (gBattleWork->unk0B54[i] != 0)
        {
            sub_0806FE84(gBattleWork->unk0B54[i]);
            gBattleWork->unk0B54[i] = 0;
        }
    }
}

/*
 * NOTE (parked): DIFF, 28/108 bytes (25.9%), same_size.
 * Logic verified correct (init 4 BattleWork fields to 0, then free/clear a
 * 4-entry pointer array gBattleWork->unk0B54[i] via sub_0806FE84). agbcc
 * consistently CSEs the repeated `gBattleWork->unkXXXX` base-pointer loads
 * differently than retail: retail keeps r5=0 live across the whole function
 * (reused as both the zero-store value AND part of loop setup) and computes
 * field addresses via an accumulating r3 offset (+0,+4,+8) reloading the
 * base pointer fresh only for the 4th field (unk0B78) and the loop. This
 * build instead re-derives the constant 0 per-statement and uses different
 * temp registers per access. Tried: caching `gBattleWork` in a local
 * `struct BattleWork *w` (made it worse, 18.5%, wrong size too — extra
 * register pressure). Plain direct `gBattleWork->fieldN = 0;` four times
 * (no cache) gives the closest result (25.9%) but still diverges from
 * instruction 2 onward.
 * New struct fields added (BattleWork, offsets 0xB54-0xB7C) are verified
 * correct via retail asm addresses — keep them if not already re-added.
 * Next: try decomp-permuter on this one (small, cheap), or hand-order the
 * field writes with a plain sequence of separate top-level statements using
 * a shared `s32 zero = 0;` local matching retail's persistent r5.
 */
