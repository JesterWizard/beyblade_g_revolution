#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061564
/* match-compiler: old_agbcc */
// Run a text control stream: 7 = set cursor (x, y), 8 = palette bank,
// 10 = new line (wrapping the row) then set cursor; anything else is logged.
void TextDraw(u8 *data)
{
    u8 op;
    u8 x;
    u8 *cur;
    struct Unk0798 *work;

    if (data == NULL || (op = *data) == 0)
        return;
    cur = data + 1;
    do
    {
        switch (op)
        {
        case 10:
            work = gUnk_03000798;
            work->unk90 = 0;
            work->unk92 = work->unk92 + work->unkA2;
            if ((s16)work->unk92 > (work->unk9A >> 3) - 1)
                work->unk92 = 0;
        case 7:
            x = *cur++;
            TextSetCursor(x, *cur++);
            break;
        case 8:
            TextSetPaletteBank(*cur++);
            break;
        default:
            _08073C44((void *)(u32)op, (void *)gData_080BB644[0]);
            break;
        }
    } while ((op = *cur++) != 0);

}

