#include "global.h"

/*
 * WIP — not byte-matched (89.4%, 93/104 bytes, same_size DIFF).
 * Logic verified correct. Only remaining diff: a call to
 * sub_08035908() (declared `u8` return) used in a truthiness test emits an
 * extra `lsls r0,r0,#24` in this build that retail does not have. Tried:
 * `if (f(...))`, `if (f(...) != 0)`, storing into a `u8` local first,
 * storing into an `s32` local first — all produce the identical 4-byte
 * diff (the shift instruction). sub_08034FBC.c uses a similar `u8 v = f();
 * return v;` pattern successfully elsewhere, but that idiom didn't transfer
 * here (different surrounding control-flow depth). Needs either a different
 * source shape or a permuter pass targeting just that one instruction.
 *
 * Also required two new struct type extensions (already landed in
 * include/unknown-types.h as part of a prior session? verify before
 * reapplying):
 *   - struct Unk0380Target (big struct pointed to by Unk0380.unk00,
 *     fields unk2CC/unk310/unk312)
 *   - struct Unk0380.unk00 changed from filler to `struct Unk0380Target *`
 * Re-check current include/unknown-types.h before resuming — these edits
 * were reverted with the C when this was parked.
 * @ 0x08033dd4
 */
void sub_08033DD4(void)
{
    struct Unk0380 *p = (struct Unk0380 *)gUnk_03000380;
    struct Unk0380Target *t = p->unk00;

    if (t->unk310 == 0 && t->unk2CC != 7 && t->unk312 == 0)
    {
        if (p->unk0A != 0 && p->unk09 != 0)
        {
            sub_08035884(&p->unk0C);
            if (sub_08035908(&p->unk0C) != 0)
                sub_08033C1C();
        }
        else
        {
            sub_08033E3C((struct Unk33F30 *)p);
        }
        return;
    }

    if (p->unk09 != 0)
        sub_08033C1C();
}
