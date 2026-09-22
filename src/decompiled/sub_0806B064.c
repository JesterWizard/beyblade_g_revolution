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
s32 sub_0806B064(struct Unk6B3E8 *a)
{
    struct Unk6B3E8Item *item;
    s32 total;
    u16 spaces;
    u16 i;

    spaces = 0;
    total = 0;
    i = 0;
    for (; i < a->unk04; i++)
    {
        item = &a->unk00[i];
        if (a->unk10 != 0 && a->unk10[i + spaces] == 0x20)
        {
            total += 5;
            spaces++;
        }
        if (item->unk70 != 0)
        {
            if (a->unk28 != 0)
                total += item->unk10 - *((const u8 *)a->unk28 + item->unk22);
            else
                total += item->unk10;
        }
    }
    total = (a->unk24 * total) >> 8;
    return total;
}
