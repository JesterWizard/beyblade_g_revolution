#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806e31c
// Samples keyframe track `b` of `a` at time `d` (22.10 fixed point, clamped to
// the last key): linearly interpolates the x/y/z of the two surrounding keys into
// out[0..2], and stores the fraction and key index in out[3], out[4]. Returns out.
u32 sub_0806E31C(void *a, void *b, s32 *out, s32 d)
{
    struct Unk6E31CTrack *track = (struct Unk6E31CTrack *)sub_0806DEC8(a, (s32)b);
    u32 *keys = track->unk20;
    s32 idx;
    s32 *p0;
    s32 *p1;

    if (d < 0)
        d = 0;
    if ((d >> 10) >= track->unk00)
        d = ((track->unk00 - 1) << 10) | (d & 0x3FF);
    idx = d >> 10;
    p0 = (s32 *)sub_0806DEF4(a, keys[idx]);
    p1 = (s32 *)sub_0806DEF4(a, keys[idx + 1]);
    out[0] = p0[0] + (((p1[0] - p0[0]) * (d & 0x3FF)) >> 10);
    out[1] = p0[1] + (((p1[1] - p0[1]) * (d & 0x3FF)) >> 10);
    out[2] = p0[2] + (((p1[2] - p0[2]) * (d & 0x3FF)) >> 10);
    out[3] = d & 0x3FF;
    out[4] = idx;
    return (u32)out;
}

