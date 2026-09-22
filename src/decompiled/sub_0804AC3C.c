#include "global.h"

void sub_0804AC3C(u8 *data)
{
    u8 *ptr;
    u8 first;
    u8 second;
    u32 coordinate;

    ptr = data;
    first = ptr[0x2D5];
    second = ptr[0x2FC];
    sub_08061BE8();
    sub_0804AAF0(ptr);

    coordinate = (u32)(((s32)(s8)second << 16) + 0x70000) >> 16;
    TextRowSetPaletteBank(coordinate, 0x0F, 4, 0x19);
    coordinate = (u32)(((s32)(s8)first << 16) + 0x70000) >> 16;
    TextRowSetPaletteBank(coordinate, 0x0E, 4, 0x19);

    VBlankIntrWait();
    _08073C40(*(void **)0x080BB888);
    sub_0804AE94();
}
