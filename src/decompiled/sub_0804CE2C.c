#include "global.h"

void sub_0804CE2C(u8 *data, s32 index, void *image)
{
    s32 idx;
    s32 first;

    idx = index;
    if (idx == (s8)data[0x2D5])
        sub_08061610(0x0E);
    else
        sub_08061610(0x0F);

    sub_080617C4((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    idx <<= 4;
    first = idx + 8;
    sub_080615EC(0, first);
    sub_0806171C(
        (void *)0x083A7EE0,
        ((u32)sub_08061784() << 16) >> 17,
        0);
    idx += 0x10;
    sub_080615EC(0, idx);
    sub_0806171C(
        (void *)0x083A7EE0,
        ((u32)sub_08061784() << 16) >> 17,
        0);
    sub_080617C4((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    sub_080615EC(0, first);
    sub_0806171C(
        image,
        ((u32)sub_08061784() << 16) >> 17,
        0);
}
