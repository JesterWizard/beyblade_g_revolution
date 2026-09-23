#include "global.h"

// @ 0x0806B3E8
// Walk a text cursor: map each non-space byte through the font table, init matching
// item slots; zero-fill any remaining slots when the string ends or slots run out.
void sub_0806B3E8(struct Unk6B3E8 *work)
{
    s32 remaining;
    const u8 *text;
    struct Unk6B3E8Item *item;
    u8 ch;
    u8 glyph;

    remaining = work->unk04;
    text = work->unk10;
    item = work->unk00;

    while (remaining > 0)
    {
        ch = *text;
        text++;
        if (ch == 0)
            break;
        if (ch == ' ')
            continue;
        glyph = ((const u8 *)0x080BB748)[ch];
        sub_0806833C((struct Unk68598 *)item, 0, glyph);
        item->unk70 = -1;
        item++;
        remaining--;
    }

    while (remaining > 0)
    {
        item->unk70 = 0;
        item++;
        remaining--;
    }
}
