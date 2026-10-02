#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_080360BC */
// @ 0x080360bc

void MotionSetVelocityToward(struct Unk360BC *a, s32 x, s32 y, s32 scale)
{
    s32 dx;
    s32 dy;
    u16 speed;
    s32 vx;
    s32 vy;

    dx = (x - a->unk0C) >> 8;
    dy = (y - a->unk10) >> 8;
    speed = Sqrt(dx * dx + dy * dy);
    vx = Div(dx << 8, speed);
    vy = Div(dy << 8, speed);
    a->unk18 = (scale * vx) >> 8;
    a->unk1C = (scale * vy) >> 8;
}

/* fn: sub_08036264 */
// @ 0x08036264
void MotionMidpoint(struct Unk36264 *out, struct Unk360BC *a, struct Unk360BC *b, s32 scale)
{
    s32 dx;
    s32 dy;
    s32 dist;

    dx = (a->unk0C - b->unk0C) >> 8;
    dy = (a->unk10 - b->unk10) >> 8;
    dist = Sqrt(dx * dx + dy * dy) << 16;
    out->unk00 = a->unk0C + ((scale * ((b->unk0C - a->unk0C) >> 1)) >> 8);
    out->unk04 = a->unk10 + ((scale * ((b->unk10 - a->unk10) >> 1)) >> 8);
    out->unk08 = (((u32)dist >> 18) + 0xFFFFFEFC) << 8;
}

/* fn: sub_08041980 */
// @ 0x08041980
void ActorPoolClear(void)
{
    struct Actor **p;
    s32 n;
    struct Actor *z;

    p = (struct Actor **)gUnk_03000480;
    z = 0;
    n = 31;
    do
    {
        if (*p != 0)
            SceneObjFreeResources(*p);
        *p = z;
        p++;
        n--;
    } while (n >= 0);
    *(u16 *)gUnk_03000504 = 0;
}

/* fn: sub_08041DB4 */
// @ 0x08041db4
void *ActorFindByIdSide(u32 a, u32 b)
{
    s16 i;
    s16 count;
    struct Actor **pool;
    struct Actor *p;

    i = 0;
    count = *(s16 *)gUnk_03000504;
    if (count > 0 && i < count)
    {
        pool = (struct Actor **)gUnk_03000480;
        do
        {
            p = pool[i];
            if (p != 0 && p->unkD4 == (void *)a && p->unkD8 == (void *)b)
                return p;
            i++;
        } while (i < count);
    }
    return 0;
}

/* fn: sub_080686F4 */
// @ 0x080686f4
/* match-compiler: old_agbcc */
void ActorAddMotionModifier(struct Unk68798 *a, s32 b, s32 c, s32 d, s32 e)
{
    struct Unk68798Heap *hp;
    struct Unk68798Entry *slot;
    struct Unk68798Entry *entries;
    s32 i;
    s32 free;
    s32 count;

    if (a->unk74 == -1) {
        a->unk74 = 0;
        hp = HeapAlloc(0x40);
        if (hp == 0) {
            DebugMessage((void *)0x083A94D4);
            return;
        }
        a->unk7C = hp;
        a->unk78 = hp->unk00;
    }
    if (a->unk74 > 3) {
        free = -1;
        count = 0;
        i = 0;
        entries = a->unk78;
        for (; i < 4; i++) {
            if (entries[i].unk00 == 0) {
                if (free < 0)
                    free = i;
                count++;
            }
        }
        if (free == -1)
            slot = entries;
        else
            slot = &entries[free];
        if (count == 4) {
            a->unk74 = 0;
            slot = entries;
        }
    } else {
        slot = &a->unk78[a->unk74];
    }
    slot->unk08 = (void *)b;
    slot->unk00 = d;
    slot->unk04 = e;
    slot->unk0C = c;
    a->unk74++;
}

/* fn: sub_08068798 */
// @ 0x08068798
void ActorApplyMotionModifiers(struct Unk68798 *state)
{
    struct Unk68798 *work;
    s32 count;
    s32 i;
    struct Unk68798Entry *entry;
    u32 offset;
    struct Unk68798Entry *entries;
    s32 value;
    s32 delta;

    work = state;
    count = work->unk74;
    if (count == -1)
        return;
    for (i = 0; i < count; i++)
    {
        offset = i << 4;
        entries = work->unk78;
        entry = (struct Unk68798Entry *)((u8 *)entries + offset);
        value = (s32)(u32)entry->unk08;
        if (value != 0)
        {
            if (entry->unk00 == 0)
                continue;
            if (entry->unk04 <= 0)
                _08073C48(work, entry, (void *)(u32)value);
        }
        value = entry->unk00;
        if (value > 0)
        {
            delta = gUnk_03000180.unk00 - gUnk_03000180.unk04;
            if (entry->unk04 > 0)
                entry->unk04 -= delta;
            else
                entry->unk00 -= delta;
            if (entry->unk00 < 0)
                entry->unk00 = 0;
        }
    }
}
