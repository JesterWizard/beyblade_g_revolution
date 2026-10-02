#include "global.h"
#include "ram_map.h"
#include "battle.h"

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

