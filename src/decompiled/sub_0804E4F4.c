#include "global.h"

void sub_0804E4F4(u8 *data, s32 index, void *image)
{
    s32 first;

    if (index == (s8)data[0x2D5])
        TextSetPaletteBank(0x0E);
    else
        TextSetPaletteBank(0x0F);
    TextSetActiveObject((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    index <<= 4;
    first = index + 8;
    TextSetCursor(0, first);
    TextDrawAlign(
        (void *)0x083A8424,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);
    index += 0x10;
    TextSetCursor(0, index);
    TextDrawAlign(
        (void *)0x083A8424,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);
    TextSetActiveObject((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    TextSetCursor(0, first);
    TextDrawAlign(
        image,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);
}
