#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806b064
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x0806B064
// Width measure over the 0xDC-stride item array: skips a leading space run into
// `spaces`, adds 5 per extra space, accumulates each item's glyph width minus its
// kerning delta, then scales by unk24 and normalises by 8.
// The final `total = ...; return total;` is load-bearing: it keeps `total` live
// into the return and gives it one more reference than the struct pointer, which
// is what makes agbcc give r3 to `total` and r4 to the pointer (retail) instead
// of the reverse.
s32 AnimTextRowMeasure(struct AnimTextRow *a)
{
    struct AnimTextItem *item;
    s32 total;
    u16 spaces;
    u16 i;

    spaces = 0;
    total = 0;
    i = 0;
    for (; i < a->count; i++)
    {
        item = &a->items[i];
        if (a->text != 0 && a->text[i + spaces] == 0x20)
        {
            total += 5;
            spaces++;
        }
        if (item->visible != 0)
        {
            if (a->kernTable != 0)
                total += item->width - *((const u8 *)a->kernTable + item->frame);
            else
                total += item->width;
        }
    }
    total = (a->scale * total) >> 8;
    return total;
}

