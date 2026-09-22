#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806e420
s32 sub_0806E420(struct Unk6E420Obj *a, struct Unk6E420Model *b, struct Unk6E420Out *c,
                 u32 d, s32 e, s32 f, s32 g, s32 h)
{
    struct Unk6E420Vec *p1;
    struct Unk6E420Vec *p2;
    u32 *idx;
    s32 dx;
    s32 dy;
    s32 den;
    s32 num;
    s32 t;
    s32 w;
    s32 v;

    if (b == 0)
        return 0;
    idx = b->unk20;
    p1 = &a->unk04[idx[d]];
    p2 = &a->unk04[idx[d + 1]];
    w = g - e;
    v = h - f;
    dx = p2->unk00 - p1->unk00;
    dy = p2->unk04 - p1->unk04;
    den = dx * v - dy * w;
    if (den == 0)
        return 0;
    num = (p1->unk04 - f) * w + v * e - p1->unk00 * v;
    t = Div(num << 10, den);
    {
        s32 x = p1->unk00 + ((dx * t) >> 10);
        s32 y = p1->unk04 + ((dy * t) >> 10);
        c->unk00 = x;
        c->unk04 = y;
    }
    c->unk08 = p1->unk08 + (((p2->unk08 - p1->unk08) * t) >> 10);
    c->unk0C = t;
    return 1;
}

