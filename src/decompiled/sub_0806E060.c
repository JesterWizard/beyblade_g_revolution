/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

struct KeySeg
{
    u8 filler_00[8];
    s16 unk08;
    s16 unk0A;
    u8 filler_0C[4];
};

struct KeyTrack
{
    s32 unk00;
    u8 filler_04[0x1C];
    u32 unk20[1];
};

u32 sub_0806E060(void *a, void *b, s32 *out, s32 d)
{
    struct KeyTrack *track = (struct KeyTrack *)ChunkListAt(a, (s32)b);
    u32 *keys = track->unk20;
    struct KeySeg *segs = (struct KeySeg *)(track->unk20 + track->unk00);
    s32 idx;
    s32 f;
    s32 *p0;
    s32 *p1;
    s16 s0;
    s16 s1;
    s16 next;
    s16 cur;
    u16 ang2;

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
        next = segs[idx + 1].unk08;
        s1 = segs[idx + 1].unk0A;
    }
    else
    {
        next = segs[idx].unk08;
        s1 = next;
    }
    ang2 = next - 0x80;
    if ((s16)ang2 < 0)
        ang2 = (s16)ang2 + 0x100;
    cur = segs[idx].unk08;
    if (s0 == cur || s1 == cur)
    {
        out[0] = p0[0] + (((p1[0] - p0[0]) * f) >> 10);
        out[1] = p0[1] + (((p1[1] - p0[1]) * f) >> 10);
    }
    else
    {
        u8 a1;
        u8 a2;
        s32 t1x;
        s32 t1y;
        s32 t2x;
        s32 t2y;
        s32 mx;
        s32 my;
        s32 q0x;
        s32 q0y;
        s32 q1x;
        s32 q1y;

        if (idx > 0)
            a1 = segs[idx - 1].unk08;
        else
            a1 = segs[0].unk08;
        a2 = ang2;
        t1x = ((gData_083C9544[a1 + 0x40] * 0x180) >> 8) + p0[0];
        t1y = ((gData_083C9544[a1] * 0x180) >> 8) + p0[1];
        t2x = ((gData_083C9544[a2 + 0x40] * 0x180) >> 8) + p1[0];
        t2y = ((gData_083C9544[a2] * 0x180) >> 8) + p1[1];
        mx = (t1x + t2x) >> 1;
        my = (t1y + t2y) >> 1;
        q0x = p0[0] + (((mx - p0[0]) * f) >> 10);
        q0y = p0[1] + (((my - p0[1]) * f) >> 10);
        q1x = mx + (((p1[0] - mx) * f) >> 10);
        q1y = my + (((p1[1] - my) * f) >> 10);
        out[0] = q0x + (((q1x - q0x) * f) >> 10);
        out[1] = q0y + (((q1y - q0y) * f) >> 10);
    }
    out[2] = p0[2] + (((p1[2] - p0[2]) * f) >> 10);
    out[3] = f;
    out[4] = idx;
    return (u32)out;
}
