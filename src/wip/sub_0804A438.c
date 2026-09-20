#include "global.h"

void sub_0804A438(u8 *data, s32 index_arg, void *image)
{
    s32 offset;
    s32 first_y;
    void *table;
    void *out;

    out = image;
    if (index_arg == (s8)data[0x2D5])
        sub_08061610(0x0E);
    else
        sub_08061610(0x0F);

    sub_080617C4((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    offset = index_arg << 4;
    first_y = offset + 8;
    sub_080615EC(0, first_y);
    table = (void *)0x083A7404;
    sub_0806171C(table, (u32)(sub_08061784() << 16) >> 17, 0);
    offset += 0x10;
    sub_080615EC(0, offset);
    sub_0806171C(table, (u32)(sub_08061784() << 16) >> 17, 0);

    sub_080617C4((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    sub_080615EC(0, first_y);
    sub_0806171C(out, (u32)(sub_08061784() << 16) >> 17, 0);
}
