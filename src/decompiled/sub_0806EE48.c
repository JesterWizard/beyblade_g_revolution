#include "global.h"

// @ 0x0806ee48
// 122/124 same size. Handler/callback dispatch plus a 4-slot motion scan; the
// remaining delta is 2 bytes in the bit-clear path.
// `flags` must be a *local* so the test and the clear share one `ldrb r1,[r2]`
// (retail reuses r1 for both), and the mask must come from a `s32 m = -2;`
// variable -- `flags & -2` folds to `flags & 0xFE`, losing retail's
// `movs r0,#2; negs r0,r0; ands r0,r1`. Only the and's destination register
// differs now: retail writes r0 (`and r0,r0,r1` + `strb r0,[r2]`), agbcc r1.
void sub_0806EE48(struct Unk6EE48 *state)
{
    struct Unk6EE48 *work;
    void *handler;
    u8 *flag_ptr;
    u32 flags;
    void *callback;
    u8 i;

    work = state;
    handler = work->unk224;
    if (handler != 0)
    {
        flag_ptr = &work->unk354;
        flags = *flag_ptr;
        if ((flags & 1) == 0)
        {
            callback = work->unk344;
            if (callback == 0)
                sub_0806EEC8(work);
            else
                _08073C48(handler, work, callback);
        }
        else
        {
            s32 m = -2;
            *flag_ptr = m & flags;
        }
    }
    for (i = 0; i < 4; i++)
    {
        if (work->unk220->entries[i].unk00 != 0)
            sub_08068E54(&work->motion[i]);
    }
}
