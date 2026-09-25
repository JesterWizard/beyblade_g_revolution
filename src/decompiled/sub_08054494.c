#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* match-compiler: old_agbcc */

void sub_08054454(void);
void sub_08070604(struct Unk70604 *dst, struct Unk70604Src *src, s32 unk20, s16 x, s16 y, u16 unk0C, u16 unk08);

// @ 0x08054494
void sub_08054494(s32 x, s32 y)
{
    struct Unk070C **loc;
    struct Unk070C *p;
    s32 i;
    s32 x8;
    s32 y8;
    s32 xEnd;
    s32 yEnd;
    struct Unk705DC *obj;

    sub_08054454();
    loc = (struct Unk070C **)0x0300070C;
    p = *loc;
    if (p == 0)
        return;

    i = 0;
    y8 = y << 8;
    xEnd = x + 4;
    yEnd = y + 4;
    x8 = x << 8;

    for (; i <= 0x0C; i++)
    {
        obj = (struct Unk705DC *)BtlObjPoolAlloc(0x0A);
        p = *loc;
        p->unk00[i] = obj;
        sub_0806FF58(obj, (void *)0x081232A4, x8, y8, 1, 0, 0, 1);
        if (i == 0)
        {
            p = *loc;
            ((struct Unk705DC *)p->unk00[0])->unk18 = (u16)i;
        }
        if (i == 0x0C)
        {
            p = *loc;
            ((struct Unk705DC *)p->unk00[0x0C])->unk18 = 2;
        }
        x8 += 0x1000;
    }

    p = *loc;
    sub_08070604((struct Unk70604 *)&p->unk34, (struct Unk70604Src *)0x082BB648,
                 (s32)0x080B7258, (s16)xEnd, (s16)yEnd, 0xF0, 0);
    p = *loc;
    sub_080712CC((struct Unk712CC *)&p->unk34, 1);
}
