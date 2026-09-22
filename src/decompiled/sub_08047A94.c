#include "global.h"

void sub_08047A94(u8 *a, s32 index_arg, u32 image)
{
    s32 input;
    u32 output;
    s32 index;
    u16 value;
    u16 y;

    input = index_arg;
    output = image;
    if (input == (s8)a[0x2D5])
        TextSetPaletteBank(0x0E);
    else
        TextSetPaletteBank(0x0F);

    TextSetActiveObject((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    index = input << 4;
    y = index + 0x28;
    TextSetCursor(0, y);
    value = TextGetAreaWidth();
    value = (value << 16) >> 17;
    TextDrawAlign((void *)0x083A6BE0, value, 0);
    y = index + 0x30;
    TextSetCursor(0, y);
    value = TextGetAreaWidth();
    value = (value << 16) >> 17;
    TextDrawAlign((void *)0x083A6BE0, value, 0);

    TextSetActiveObject((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    TextSetCursor(0, index + 0x28);
    value = TextGetAreaWidth();
    value = (value << 16) >> 17;
    TextDrawAlign((void *)output, value, 0);
}
