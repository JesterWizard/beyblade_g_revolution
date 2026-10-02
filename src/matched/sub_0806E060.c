#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806e060
// Curved variant of KeyframeTrackSample: samples keyframe track `b` of `a` at
// time `d` (22.10 fixed point, clamped to the last key). Unless the segment's
// heading equals either neighbour's s16 at +0x0A, x/y follow a quadratic Bezier
// from p0 to p1 whose control point averages p0 pushed 0x180 along the previous
// segment's heading and p1 pushed 0x180 back against the next one's; otherwise
// x/y are linear. z is always linear. Stores the fraction and key index in
// out[3], out[4] and returns out.
u32 KeyframeBezierSample(void *a, void *b, s32 *out, s32 d)
{
    struct Unk6E31CTrack *track = (struct Unk6E31CTrack *)ChunkListAt(a, (s32)b);
    u32 *keys = track->unk20;
    struct Unk6E060Seg *segs = (struct Unk6E060Seg *)(track->unk20 + track->unk00);
    s32 radius = 0x180;
    s32 idx;
    s32 f;
    s32 *p0;
    s32 *p1;
    s16 s0;
    s16 s1;
    s16 angle;
    s16 prevAngle;
    s32 x;
    s32 y;
    s32 x1;
    s32 y1;
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;

    if (d < 0)
        d = 0;
    if ((d >> 10) >= track->unk00)
        d = ((track->unk00 - 1) << 10) | (d & 0x3FF);
    idx = d >> 10;
    p0 = (s32 *)PosRecordGet(a, keys[idx]);
    p1 = (s32 *)PosRecordGet(a, keys[idx + 1]);
    f = d & 0x3FF;
    s0 = segs[idx].unk0A;
    if (idx < track->unk00 - 2)
    {
        angle = segs[idx + 1].unk08;
        s1 = segs[idx + 1].unk0A;
    }
    else
    {
        angle = segs[idx].unk08;
        s1 = angle;
    }
    angle -= 0x80;
    if (angle < 0)
        angle += 0x100;
    if (s0 != segs[idx].unk08 && s1 != segs[idx].unk08)
    {
        if (idx > 0)
            prevAngle = segs[idx - 1].unk08;
        else
            prevAngle = segs[0].unk08;
        x = (gData_083C9544[(u8)prevAngle + 0x40] * radius) >> 8;
        y = (gData_083C9544[(u8)prevAngle] * radius) >> 8;
        x += p0[0];
        y += p0[1];
        x1 = (gData_083C9544[(u8)angle + 0x40] * radius) >> 8;
        y1 = (gData_083C9544[(u8)angle] * radius) >> 8;
        x1 += p1[0];
        y1 += p1[1];
        // control point
        x = (x + x1) >> 1;
        y = (y + y1) >> 1;
        ax = p0[0] + (((x - p0[0]) * f) >> 10);
        ay = p0[1] + (((y - p0[1]) * f) >> 10);
        bx = x + (((p1[0] - x) * f) >> 10);
        by = y + (((p1[1] - y) * f) >> 10);
        x = ax + (((bx - ax) * f) >> 10);
        y = ay + (((by - ay) * f) >> 10);
        out[0] = x;
        out[1] = y;
    }
    else
    {
        out[0] = p0[0] + (((p1[0] - p0[0]) * f) >> 10);
        out[1] = p0[1] + (((p1[1] - p0[1]) * f) >> 10);
    }
    out[2] = p0[2] + (((p1[2] - p0[2]) * f) >> 10);
    out[3] = f;
    out[4] = idx;
    return (u32)out;
}

