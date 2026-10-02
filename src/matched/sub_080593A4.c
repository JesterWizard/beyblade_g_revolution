#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080593a4
void SegmentedBarRebuild(struct SegmentedBar *a)
{
    s32 i;
    s32 last;
    s32 count;

    for (i = 0; i <= 7; i++)
    {
        if (a->segments[i] != NULL)
        {
            BtlObjPoolFree(a->segments[i]);
            a->segments[i] = NULL;
        }
    }
    count = (a->endAnchor->x >> 8) - ((a->startAnchor->x + a->startOffset) >> 8);
    last = DivRemainder(count, 32);
    count >>= 5;
    if (last > 24)
        last = 24;
    for (i = 0; i <= count; i++)
    {
        if (i == 0)
        {
            a->segments[0] = BtlObjPoolAlloc(10);
            SpriteInitFromTemplate(a->segments[0], (void *)0x0810E628, a->startAnchor->x + a->startOffset, a->endAnchor->y, 0, 0, 0, (u16)last);
            TextEntrySetPaletteBank(a->segments[0], 9);
            if (i < count)
                a->segments[0]->unk18 = 24;
        }
        else
        {
            a->segments[i] = BtlObjPoolAlloc(10);
            SpriteInitFromTemplate(a->segments[i], (void *)0x081178B0, a->startAnchor->x + a->startOffset + (i << 13), a->endAnchor->y, 0, 0, 0, (u16)last);
            TextEntrySetPaletteBank(a->segments[i], 9);
            if (i < count)
                a->segments[i]->unk18 = 24;
        }
    }
}


