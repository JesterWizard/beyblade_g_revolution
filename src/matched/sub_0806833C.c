#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806833c
/* match-compiler: old_agbcc */
void sub_0806833C(struct Unk68598 *a, s32 b, u16 c)
{
    struct Unk68014 *p;
    struct Unk68014Rec *rec;
    struct Unk68014Rec *e;
    u8 *q;
    u32 m;
    u16 w;
    u16 h;
    u8 f;
    u8 g;

    rec = AnimRecAt((struct Unk68014 **)a, b);
    p = a->unk00;
    m = p->unk00 << 1;
    if (m & 2)
        m += 2;
    if ((p->unk07 & 0x10) != 0) {
        e = &p->unk20[p->unk08];
        q = (u8 *)e + m;
        if (q != 0) {
            q += b << 4;
            a->unkA4 = q[0];
            a->unkA5 = q[1];
        }
    }
    w = rec->unk00;
    h = rec->unk02;
    if (c < h) {
        f = rec->unk07;
        g = rec->unk06;
        a->unk32 = g;
        a->unk33 = f;
        a->unk34 = rec->unk04;
        a->unk36 = 0;
        a->unk26 = h;
        a->unk20 = b;
        a->unk24 = 0;
        a->unk22 = w + c;
        a->unk31 = (f & 0x0C) >> 2;
    }
}

