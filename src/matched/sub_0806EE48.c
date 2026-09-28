#include "global.h"

// @ 0x0806ee48
// Handler/callback dispatch plus a 4-slot motion scan.
// Two shapes are load-bearing in the bit-clear path:
//  - the clean path re-reads the byte as `m & *flag_ptr` rather than masking a
//    cached copy: mask the cached value and agbcc writes the `and` result into
//    r1, while retail writes r0. The `ldrb` is still shared (agbcc CSEs the two
//    `*flag_ptr` reads) and the mask must be a `s32` local so agbcc emits
//    `movs r0,#2; negs r0,r0` instead of folding a literal -2 to `& 0xFE`.
void CameraUpdate(struct MapView *state)
{
    struct MapView *work;
    void *handler;
    u8 *flag_ptr;
    void *callback;
    u8 i;

    work = state;
    handler = work->target;
    if (handler != 0)
    {
        flag_ptr = &work->flags;
        if ((*flag_ptr & 1) == 0)
        {
            callback = work->targetHandler;
            if (callback == 0)
                CameraEaseToTarget(work);
            else
                _08073C48(handler, work, callback);
        }
        else
        {
            s32 m = -2;
            *flag_ptr = m & *flag_ptr;
        }
    }
    for (i = 0; i < 4; i++)
    {
        if (work->follow->entries[i].active != 0)
            sub_08068E54(&work->layers[i]);
    }
}
