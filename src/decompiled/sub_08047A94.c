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
        sub_08061610(0x0E);
    else
        sub_08061610(0x0F);

    sub_080617C4((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    index = input << 4;
    y = index + 0x28;
    sub_080615EC(0, y);
    value = sub_08061784();
    value = (value << 16) >> 17;
    sub_0806171C((void *)0x083A6BE0, value, 0);
    y = index + 0x30;
    sub_080615EC(0, y);
    value = sub_08061784();
    value = (value << 16) >> 17;
    sub_0806171C((void *)0x083A6BE0, value, 0);

    sub_080617C4((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    sub_080615EC(0, index + 0x28);
    value = sub_08061784();
    value = (value << 16) >> 17;
    sub_0806171C((void *)output, value, 0);
}
