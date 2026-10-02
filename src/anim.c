#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_08067BB8 */
// @ 0x08067bb8
/* match-compiler: old_agbcc */
// Construct an animated object from its template: position (x, y, z in pixels,
// stored 24.8), defaults for every state field, then frame/palette setup.
void AnimObjCreate(struct AnimObj *obj, struct Unk67BB8Source *src, s32 arg2, s32 x, s32 y, s32 z, s32 arg6)
{
    obj->data = src;
    obj->lastAdvanceTick = gUnk_03000180.unk00;
    obj->unk3C = arg2;
    obj->countdown = arg6;
    obj->x = x << 8;
    obj->y = y << 8;
    obj->z = z << 8;
    obj->unk16 = 0;
    obj->unk12 = 0x100;
    obj->unk14 = 0x100;
    obj->unkA0 = 0;
    obj->unkA2 = 0;
    obj->unkA4 = 0;
    obj->unkA5 = 0;
    obj->velX = 0;
    obj->velY = 0;
    obj->velZ = 0;
    obj->accelX = 0;
    obj->accelY = 0;
    obj->accelZ = 0;
    obj->damping = 0x10;
    obj->unk18 = 0;
    obj->unk64 = 0;
    obj->frame = 0;
    obj->prevFrame |= 0xFFFF;
    obj->seqKey |= 0xFFFF;
    obj->seqOffset = 0;
    obj->seqStep = 0;
    obj->recIndex = 0;
    obj->unk2C = 0;
    obj->seqNextKey |= 0xFFFF;
    obj->unk10 = src->unk04;
    obj->unk11 = src->unk05;
    obj->unk30 = src->unk06;
    obj->unk2A = src->unk08;
    obj->unk38 = src->unk07;
    obj->unk28 = src->unk14;
    obj->flip = 0;
    obj->unk39 = 0;
    obj->unk3B = 0;
    obj->unk3A = src->unk0C;
    obj->animHold = 0;
    obj->unk74 = -1;
    obj->unk78 = 0;
    obj->unk7C = 0;
    obj->path = 0;
    obj->pathStep = -1;
    obj->unk88 = 0;
    obj->unk8C = 0;
    obj->unk8D = 0;
    obj->flags = 0;
    obj->unk90 = 0;
    obj->unk94 = 0;
    obj->unkB0 = 0;
    obj->unkB4 = 0;
    sub_08068574((struct Actor *)obj, obj->unk10 >> 1, obj->unk11, 0);
    sub_08068558((struct Actor *)obj, 0, 0, obj->unk10, obj->unk11);
    obj->unkB8 = 0;
    obj->unkBC = 0;
    AnimObjSetRecord((struct AnimObjPlayback *)obj, 0);
    obj->onFinish = 0;
}

/* fn: sub_08067F3C */
// @ 0x08067f3c
/* match-compiler: old_agbcc */
// Sum `rec->unk02` halfwords from the animation's halfword table starting at
// `rec->unk00`, on top of the base value `rec->unk04 * rec->unk02`.
s32 AnimHalfwordSum(void *a, u32 v)
{
    struct Unk67F3C *obj = a;
    struct AnimData *inner;
    struct AnimRecord *rec;
    u16 *base;
    u16 *p;
    u32 n;
    s32 sum;
    u32 start;
    u32 i;

    inner = obj->unk00;
    rec = AnimRecAt(&obj->unk00, v);
    base = AnimHalfwordBase(inner);
    n = rec->length;
    sum = rec->delay * n;
    start = rec->start;
    if ((s32)v >= (s32)inner->recordCount)
        return 0;
    if (base != 0 && !(obj->unk98 & 4) && n != 0)
    {
        p = &base[start];
        i = n;
        do
        {
            sum += *p++;
        } while (--i != 0);
    }
    return sum;
}

/* fn: sub_08067FC8 */
// @ 0x08067fc8

u32 AnimDurationForKey(void *a, u32 b)
{
    void *obj;
    u16 key;
    u32 total;
    struct AnimSeqEntry *p;
    u32 i;
    struct AnimSeqEntry *cursor;

    obj = a;
    key = (u16)b;
    total = 0;
    p = sub_08067F98(obj, key);
    if (p == 0)
        return 0;
    i = 0;
    if (total >= p->stepCount)
        goto done;
    cursor = p;
    do
    {
        total += AnimHalfwordSum(obj, cursor->firstRecord);
        cursor = (struct AnimSeqEntry *)((u16 *)cursor + 1);
        i++;
    } while (i < p->stepCount);
done:
    return total;
}

/* fn: sub_08068014 */
// @ 0x08068014

void *AnimRecAt(struct AnimData **slot, u32 i)
{
    struct AnimRecord *p;

    p = (*slot)->unk20;
    return &p[i];
}

/* fn: sub_08068020 */
// @ 0x08068020

void AnimObjSelectSeq(struct AnimObjSeqSelect *a, u16 key, u16 arg2)
{
    struct AnimData *inner;
    struct AnimSeqEntry *rec;
    u32 i;
    u32 off;
    u32 acc;

    acc = 0;
    inner = a->data;
    rec = (struct AnimSeqEntry *)((u8 *)inner + inner->seqTableOffset);
    i = 0;
    while (i < a->seqCount)
    {
        if (rec->key == key)
        {
            a->seqOffset = acc;
            a->seqStep = 0;
            a->seqKey = key;
            a->seqNextKey = arg2;
            AnimObjSetRecord((struct AnimObjPlayback *)a, rec->firstRecord);
            return;
        }
        off = rec->size;
        rec = (struct AnimSeqEntry *)((u8 *)rec + off);
        acc = (u16)(acc + off);
        i++;
    }
}

/* fn: sub_080680CC */
// @ 0x080680cc
void AnimObjSelectSeqDefault(struct AnimObjSeqSelect *a, u16 key)
{
    struct AnimData *inner;
    struct AnimSeqEntry *rec;
    u32 i;
    u32 off;
    u32 acc;

    acc = 0;
    inner = a->data;
    rec = (struct AnimSeqEntry *)((u8 *)inner + inner->seqTableOffset);
    i = 0;
    while (i < a->seqCount)
    {
        if (rec->key == key)
        {
            a->seqOffset = acc;
            a->seqStep = 0;
            a->seqKey = key;
            a->seqNextKey = 0xFFFF;
            AnimObjSetRecord((struct AnimObjPlayback *)a, rec->firstRecord);
            return;
        }
        off = rec->size;
        rec = (struct AnimSeqEntry *)((u8 *)rec + off);
        acc = (u16)(acc + off);
        i++;
    }
}

/* fn: sub_08068118 */
// @ 0x08068118
/* match-compiler: old_agbcc */
void AnimObjSeqAdvance(struct AnimObjSeqStep *a)
{
    struct Unk68118Table *table;
    u16 next;
    s32 arg;

    table = (struct Unk68118Table *)((u8 *)a->data + a->data->seqTableOffset + a->seqOffset);
    if (a->seqStep < table->unk04 - 1)
    {
        next = a->seqStep + 1;
    }
    else
    {
        next = 0;
        if ((s16)a->seqNextKey != -1)
        {
            arg = a->seqKey;
            AnimObjSelectSeq((struct AnimObjSeqSelect *)a, a->seqNextKey, 0xFFFF);
            if (a->onFinish != NULL)
                _08073C48(a, (void *)arg, a->onFinish);
            return;
        }
    }
    a->seqStep = next;
    AnimObjSetRecord((struct AnimObjPlayback *)a, ((u16 *)table)[next + 4]);
}

/* fn: sub_08068180 */
// @ 0x08068180
/* match-compiler: old_agbcc */
void AnimObjSetRecord(struct AnimObjPlayback *a, u32 b)
{
    struct AnimData *p;
    struct AnimRecord *rec;
    struct AnimRecord *e;
    u8 *q;
    u32 m;
    u16 w;
    u16 h;
    u8 f;
    u8 g;

    rec = &a->data->unk20[b];
    p = a->data;
    m = p->unk00 << 1;
    if (m & 2)
        m += 2;
    if ((p->unk07 & 0x10) != 0) {
        e = &p->unk20[p->recordCount];
        q = (u8 *)e + m;
        if (q != 0) {
            q += b << 4;
            a->unkA4 = q[0];
            a->unkA5 = q[1];
        }
    }
    w = rec->start;
    h = rec->length;
    f = rec->playFlags;
    g = rec->maxLoops;
    a->maxLoops = g;
    a->playFlags = f;
    a->frameDelay = rec->delay;
    a->delayBonus = 0;
    a->lastAdvanceTick = gUnk_03000180.unk00;
    a->recLength = h;
    a->recIndex = b;
    a->loopCount = 0;
    if ((f & 2) != 0)
        a->frame = w + (h + 0xFFFF);
    else
        a->frame = w;
    a->flip ^= (f & 0x0C) >> 2;
}

/* fn: sub_0806833C */
// @ 0x0806833c
/* match-compiler: old_agbcc */
void AnimObjSetRecordAt(struct AnimObjPlayback *a, s32 b, u16 c)
{
    struct AnimData *p;
    struct AnimRecord *rec;
    struct AnimRecord *e;
    u8 *q;
    u32 m;
    u16 w;
    u16 h;
    u8 f;
    u8 g;

    rec = AnimRecAt((struct AnimData **)a, b);
    p = a->data;
    m = p->unk00 << 1;
    if (m & 2)
        m += 2;
    if ((p->unk07 & 0x10) != 0) {
        e = &p->unk20[p->recordCount];
        q = (u8 *)e + m;
        if (q != 0) {
            q += b << 4;
            a->unkA4 = q[0];
            a->unkA5 = q[1];
        }
    }
    w = rec->start;
    h = rec->length;
    if (c < h) {
        f = rec->playFlags;
        g = rec->maxLoops;
        a->maxLoops = g;
        a->playFlags = f;
        a->frameDelay = rec->delay;
        a->delayBonus = 0;
        a->recLength = h;
        a->recIndex = b;
        a->loopCount = 0;
        a->frame = w + c;
        a->flip = (f & 0x0C) >> 2;
    }
}

/* fn: sub_08068598 */
// @ 0x08068598
/* match-compiler: old_agbcc */
// Advance an animation by one frame once its delay has elapsed: the delay is
// unk34 + unk36 plus the per-frame entry from the optional delay table, never
// below the global minimum. Steps unk22 forward or back (unk33 bit 1) within
// the current record's [start, start + len), wrapping or ping-ponging (bit 0),
// counting loops in unk24; calls sub_08068118 once that reaches unk32.
void AnimAdvanceFrame(struct AnimObjPlayback *work)
{
    struct AnimRecord *rec;
    struct Unk68598Lookup *lookup;
    s32 total;
    u16 delay;
    u16 start;
    u16 len;
    u32 off;
    struct Unk68598Lookup *end;
    s32 last;

    rec = &work->data->unk20[work->recIndex];
    if (!(work->flags & 4))
    {
        off = work->data->recordCount * 8 + 0x20;
        end = (struct Unk68598Lookup *)((u8 *)work->data + work->data->seqTableOffset);
        lookup = (struct Unk68598Lookup *)((u8 *)work->data + off);
        if (lookup == end)
            lookup = NULL;
    }
    else
        lookup = NULL;
    total = work->frameDelay + work->delayBonus;
    delay = lookup != NULL ? (&lookup->unk00)[work->frame + 1] + total : total;
    if (delay < gData_03000180.unk08)
        delay = gData_03000180.unk08;
    if (gData_03000180.unk00 - work->lastAdvanceTick < delay)
        return;
    work->lastAdvanceTick += delay;
    start = rec->start;
    len = rec->length;
    work->prevFrame = work->frame;
    if (work->playFlags & 2)
        work->frame--;
    else
        work->frame++;
    if (work->frame > (last = start - 1) + len)
    {
        if (work->playFlags & 1)
        {
            work->playFlags ^= 2;
            work->frame = start + (len - 2);
        }
        else
        {
            work->frame = start;
        }
        work->loopCount++;
    }
    if (work->frame < start)
    {
        if (work->playFlags & 1)
        {
            work->playFlags ^= 2;
            work->frame = start + 1;
        }
        else
        {
            work->frame = start + (len - 1);
        }
        work->loopCount++;
    }
    if (work->maxLoops != 0 && work->loopCount >= work->maxLoops)
        AnimObjSeqAdvance((struct AnimObjSeqStep *)work);
}

/* fn: sub_08068884 */
// @ 0x08068884
/* match-compiler: old_agbcc */
void *AnimHalfwordBase(struct AnimData *a)
{
    u8 *p = (u8 *)a + (a->recordCount * 8 + 0x20);
    u8 *q = (u8 *)a + a->seqTableOffset;

    if (p == q)
        return 0;
    return p;
}

/* fn: sub_0806DF38 */
// @ 0x0806df38
// Collect up to maxCount (track, key) hits for `key` across a's keyframe
// tracks, skipping track `skip`. Each hit records the track, key index, track
// index and the 16-byte frames either side of the key. Returns the hit count.
u16 KeyframeFindHits(struct UnkDEC8 *a, struct UnkDF38Entry *out, void *skip, u16 maxCount, u32 key)
{
    u16 count;
    s32 idx;
    struct Unk6E31CTrack *track;
    u8 *frames;
    s32 i;
    u32 *keys;

    count = 0;
    for (idx = 0; idx < a->unk00->unk04; idx++)
    {
        track = (struct Unk6E31CTrack *)ChunkListAt(a, idx);
        if (track == NULL)
            break;
        if (track == skip)
            continue;
        frames = (u8 *)track->unk20 + track->unk00 * 4;
        keys = track->unk20;
        for (i = 0; i < track->unk00; i++)
        {
            if (key == keys[i])
            {
                out[count].unk00 = (s32 *)track;
                out[count].unk04 = i;
                out[count].unk08 = idx;
                out[count].unk0C = i > 0 ? frames + (i - 1) * 16 : NULL;
                if (i < track->unk00 - 1)
                    out[count].unk10 = frames + i * 16;
                else
                    out[count].unk10 = NULL;
                count++;
                if (count >= maxCount)
                    return count;
            }
        }
    }
    return count;
}

/* fn: sub_0806E060 */
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

/* fn: sub_0806E31C */
// @ 0x0806e31c
// Samples keyframe track `b` of `a` at time `d` (22.10 fixed point, clamped to
// the last key): linearly interpolates the x/y/z of the two surrounding keys into
// out[0..2], and stores the fraction and key index in out[3], out[4]. Returns out.
u32 KeyframeTrackSample(void *a, void *b, s32 *out, s32 d)
{
    struct Unk6E31CTrack *track = (struct Unk6E31CTrack *)ChunkListAt(a, (s32)b);
    u32 *keys = track->unk20;
    s32 idx;
    s32 *p0;
    s32 *p1;

    if (d < 0)
        d = 0;
    if ((d >> 10) >= track->unk00)
        d = ((track->unk00 - 1) << 10) | (d & 0x3FF);
    idx = d >> 10;
    p0 = (s32 *)PosRecordGet(a, keys[idx]);
    p1 = (s32 *)PosRecordGet(a, keys[idx + 1]);
    out[0] = p0[0] + (((p1[0] - p0[0]) * (d & 0x3FF)) >> 10);
    out[1] = p0[1] + (((p1[1] - p0[1]) * (d & 0x3FF)) >> 10);
    out[2] = p0[2] + (((p1[2] - p0[2]) * (d & 0x3FF)) >> 10);
    out[3] = d & 0x3FF;
    out[4] = idx;
    return (u32)out;
}
