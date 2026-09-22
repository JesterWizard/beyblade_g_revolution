#include "global.h"

void sub_0804CE2C(u8 *data, s32 index, void *image)
{
    s32 idx;
    s32 first;

    idx = index;
    if (idx == (s8)data[0x2D5])
        TextSetPaletteBank(0x0E);
    else
        TextSetPaletteBank(0x0F);

    TextSetActiveObject((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    idx <<= 4;
    first = idx + 8;
    TextSetCursor(0, first);
    TextDrawAlign(
        (void *)0x083A7EE0,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);
    idx += 0x10;
    TextSetCursor(0, idx);
    TextDrawAlign(
        (void *)0x083A7EE0,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);
    TextSetActiveObject((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    TextSetCursor(0, first);
    TextDrawAlign(
        image,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);
}
