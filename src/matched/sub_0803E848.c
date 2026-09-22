#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803e848
void sub_0803E848(struct Unk2F520 *a, s32 b, void *c)
{
    s32 offset;
    s32 first_y;
    void *table;
    void *out;

    out = c;
    if (b == (s8)a->unk2D5)
        TextSetPaletteBank(0x0E);
    else
        TextSetPaletteBank(0x0F);

    TextSetActiveObject((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    offset = b << 4;
    first_y = offset + 8;
    TextSetCursor(0, first_y);
    table = (void *)0x0833D408;
    TextDrawAlign(table, (u32)(TextGetAreaWidth() << 16) >> 17, 0);
    offset += 0x10;
    TextSetCursor(0, offset);
    TextDrawAlign(table, (u32)(TextGetAreaWidth() << 16) >> 17, 0);
    TextSetActiveObject((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    TextSetCursor(0, first_y);
    TextDrawAlign(out, 0x23, 2);
}

