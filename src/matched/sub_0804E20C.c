#include "global.h"

// @ 0x0804e20c

void sub_0804E20C(u8 *data)
{
    TextRowSetPaletteBank(5, 0x0F, 9, 0x14);
    TextRowSetPaletteBank(6, 0x0F, 9, 0x14);
    TextRowSetPaletteBank(7, 0x0F, 9, 0x14);
    TextRowSetPaletteBank(8, 0x0F, 9, 0x14);
    TextRowSetPaletteBank(9, 0x0F, 9, 0x14);
    TextRowSetPaletteBank(0x0A, 0x0F, 9, 0x14);
    TextRowSetPaletteBank(0x0B, 0x0F, 9, 0x14);
    TextRowSetPaletteBank(0x0C, 0x0F, 9, 0x14);
    TextRowSetPaletteBank(
        (u32)(((s32)(s8)data[0x2D5] << 17) + 0x50000) >> 16,
        0x0E,
        9,
        0x14);
    TextRowSetPaletteBank(
        (u32)(((s32)(s8)data[0x2D5] << 17) + 0x60000) >> 16,
        0x0E,
        9,
        0x14);
}

