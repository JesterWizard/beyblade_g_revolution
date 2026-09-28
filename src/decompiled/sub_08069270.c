/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

typedef void (*BlitFunc)(struct Unk68988 *, s32, s32, s32, s32, s32, s32);
typedef void (*BlitColFunc)(struct Unk68988 *, s32, s32, s32, s32);

void BgMapBlitRect(struct Unk68988 *st, s32 x, s32 y, s32 d, s32 e, s32 w, s32 h)
{
    BlitFunc blit;
    s32 len1, len2;
    s32 x2;
    s32 d2;
    s32 end;
    s32 e1, e2, h1, h2;

    len1 = w;
    h1 = h;
    len2 = 0;
    h2 = h;
    e1 = e;
    d2 = d;
    e2 = e;
    if (st->unk64 & 1)
        blit = (BlitFunc)0x0806945D;
    else
        blit = (BlitFunc)gData_080BB8A4[0];
    end = x + w;
    if (end > st->unk00)
    {
        len1 = 0;
        if (x < st->unk00)
            len1 = st->unk00 - x;
        len2 = w - len1;
        x2 = x + len1 - st->unk00;
        d2 += len1;
    }
    if (x < 0)
    {
        len1 = end;
        if (len1 < 0)
            len1 = 0;
        len2 = w - len1;
        x2 = x + st->unk00;
        x = 0;
        d += len2;
    }
    if (len1 > 0)
        blit(st, x, y, d, e1, len1, h1);
    if (len2 > 0)
    {
        if (st->unk7C & 8)
            blit(st, x2, y, d2, e2, len2, h2);
        else
            ((BlitColFunc)gData_080BB8A8[0])(st, d2, e2, len2, h2);
    }
}
