#include "global.h"

// @ 0x08051504
void sub_08048168(struct Unk2F520 *a)
{
    s8 *fieldPtr;

    TextRowSetPaletteBank(5, 0xF, 0xB, 0x12);
    TextRowSetPaletteBank(6, 0xF, 0xB, 0x12);
    TextRowSetPaletteBank(7, 0xF, 0xB, 0x12);
    TextRowSetPaletteBank(8, 0xF, 0xB, 0x12);
    fieldPtr = &a->unk2D5;
    TextRowSetPaletteBank((u16)((((s32)*fieldPtr << 17) + 0x50000) >> 16), 0xE, 0xB, 0x12);
    TextRowSetPaletteBank((u16)((((s32)*fieldPtr << 17) + 0x60000) >> 16), 0xE, 0xB, 0x12);
}
