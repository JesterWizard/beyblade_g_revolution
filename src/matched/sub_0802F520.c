#include "global.h"

// @ 0x0802f520
void sub_0802F520(struct Unk2F520 *a)
{
    s8 field2D5;
    s32 doubled;

    field2D5 = a->unk2D5;
    doubled = a->unk2FC * 2;
    TextRowSetPaletteBank(doubled + 0xC, 0xF, 4, 0x19);
    TextRowSetPaletteBank(doubled + 0xD, 0xF, 4, 0x19);
    doubled = field2D5 * 2;
    TextRowSetPaletteBank(doubled + 0xC, 0xE, 4, 0x19);
    TextRowSetPaletteBank(doubled + 0xD, 0xE, 4, 0x19);
}
