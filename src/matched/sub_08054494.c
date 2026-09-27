#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08054494
void sub_08054454(void);
void Unk70604Init(struct Unk70604 *dst, struct Unk70604Src *src, s32 unk20, s16 x, s16 y, u16 unk0C, u16 unk08);

void sub_08054494(s32 x, s32 y)
{
    s32 i;
    s32 y8;
    s32 xEnd;
    s32 yEnd;
    void *obj;

    sub_08054454();
    if (gUnk_0300070C == NULL)
        return;

    i = 0;
    y8 = y << 8;
    xEnd = x + 4;
    yEnd = y + 4;
    for (; i <= 12; i++)
    {
        obj = BtlObjPoolAlloc(0x0A);
        gUnk_0300070C->unk00[i] = obj;
        sub_0806FF58(obj, (void *)0x081232A4, (x + i * 16) << 8, y8, 1, 0, 0, 1);
        if (i == 0)
            ((struct Unk705DC *)gUnk_0300070C->unk00[0])->unk18 = i;
        if (i == 12)
            ((struct Unk705DC *)gUnk_0300070C->unk00[12])->unk18 = 2;
    }

    Unk70604Init((struct Unk70604 *)&gUnk_0300070C->unk34, (struct Unk70604Src *)0x082BB648,
                 (s32)0x080B7258, xEnd, yEnd, 0xF0, 0);
    sub_080712CC((struct Unk712CC *)&gUnk_0300070C->unk34, 1);
}

