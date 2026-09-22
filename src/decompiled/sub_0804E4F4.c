#include "global.h"

void sub_0804E4F4(u8 *data, s32 index, void *image)
{
    s32 first;

    if (index == (s8)data[0x2D5])
        sub_08061610(0x0E);
    else
        sub_08061610(0x0F);
    sub_080617C4((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    index <<= 4;
    first = index + 8;
    sub_080615EC(0, first);
    sub_0806171C(
        (void *)0x083A8424,
        ((u32)sub_08061784() << 16) >> 17,
        0);
    index += 0x10;
    sub_080615EC(0, index);
    sub_0806171C(
        (void *)0x083A8424,
        ((u32)sub_08061784() << 16) >> 17,
        0);
    sub_080617C4((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    sub_080615EC(0, first);
    sub_0806171C(
        image,
        ((u32)sub_08061784() << 16) >> 17,
        0);
}
