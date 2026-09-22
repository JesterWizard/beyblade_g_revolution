#include "global.h"

void sub_0804C27C(u8 *data, s32 index_arg, void *image)
{
    s32 index;
    s32 first;

    index = index_arg;
    if (index == (s8)data[0x2D5])
        TextSetPaletteBank(0x0E);
    else
        TextSetPaletteBank(0x0F);

    sub_080617C4((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    index <<= 4;
    first = index + 8;
    TextSetCursor(0, first);
    TextDrawAlign(
        (void *)0x083A7DF8,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);
    index += 0x10;
    TextSetCursor(0, index);
    TextDrawAlign(
        (void *)0x083A7DF8,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);

    sub_080617C4((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    TextSetCursor(0, first);
    TextDrawAlign(
        image,
        ((u32)TextGetAreaWidth() << 16) >> 17,
        0);
}
