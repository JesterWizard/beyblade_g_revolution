#include "global.h"

/*
 * WIP — not byte-matched (19.2%, 20/104 bytes, same_size DIFF — far off,
 * needs a real rewrite, not just tweaks).
 *
 * Requires new struct types (parked here for reference, re-derive/re-add
 * before reattempting — these were reverted from unknown-types.h):
 *   struct Unk338F0Table { u32 unk00; u16 unk04; };  // header word + u16 table
 *   struct Unk33958.unk04 retyped from `s32 *` to `struct Unk338F0Table *`
 *   struct Unk33958.unk02 promoted from filler_02[2] to `s16 unk02`
 *
 * KNOWN BUG in this draft: `(&table->unk04)[a->unk00]` is wrong pointer
 * arithmetic (indexes past a scalar struct member, not a real array method).
 * The real table is u16 values starting right after the header word
 * (i.e. `((u16 *)((u8 *)table + 4))[a->unk00]`, matching asm's
 * `r6 = unk04_ptr + 4; ... ldrh r0,[table*2 + r6]`). Rewrite using an
 * explicit byte-offset table pointer (not a struct member reinterpreted as
 * an array) before re-attempting — this file's version does not reflect
 * that fix yet.
 *
 * Logic sketch (from asm, offsets relative to `a`):
 *   if (a->unk00 == (s16)table->unk00) { a->unk00 = -1; return; }
 *   if (a->unk00 == -1) return;
 *   if (a->unk02 == 0 && a->unk00 == 0) return;
 *   if (a->unk02 != 0) a->unk02--;
 *   if (key == table_u16[a->unk00]) { a->unk02 = 0x3C; a->unk00 = (u16)a->unk00 + 1; }
 *   else if (key != 0) a->unk02 = 0;
 * @ 0x080338f0
 */
void sub_080338F0(struct Unk33958 *a, u16 key)
{
    struct Unk338F0Table *table = a->unk04;

    if (a->unk00 == (s16)table->unk00)
    {
        a->unk00 = -1;
        return;
    }

    if (a->unk00 == -1)
        return;

    if (a->unk02 == 0 && a->unk00 == 0)
        return;

    if (a->unk02 != 0)
        a->unk02 -= 1;

    /* BUG: see note above, wrong indexing — fix before reattempting. */
    if (key == (&table->unk04)[a->unk00])
    {
        a->unk02 = 0x3C;
        a->unk00 = (u16)a->unk00 + 1;
    }
    else if (key != 0)
    {
        a->unk02 = 0;
    }
}
