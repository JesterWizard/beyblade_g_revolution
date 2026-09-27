#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08066fb8
void sub_08066FB8(void)
{
    VBlankIntrWait();
    sub_08061BE8();
    TextRowSetPaletteBank(5, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(6, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(7, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(8, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(9, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(10, 0x0F, 3, 0x1A);
    VBlankIntrWait();

    TextSetCursor(0, 0x08);
    TextDrawAlign(gData_080BB110[gUnk_03000674].unk0C, TextGetAreaWidth() / 2, 0);
    TextSetCursor(0, 0x18);
    TextDrawAlign(gData_080BB110[gUnk_03000674 + 1].unk0C, TextGetAreaWidth() / 2, 0);
    TextSetCursor(0, 0x28);
    TextDrawAlign(gData_080BB110[gUnk_03000674 + 2].unk0C, TextGetAreaWidth() / 2, 0);

    if (gUnk_03000678 == 0)
    {
        TextRowSetPaletteBank(5, 0x0E, 3, 0x1A);
        TextRowSetPaletteBank(6, 0x0E, 3, 0x1A);
    }
    else if (gUnk_03000678 == 1)
    {
        TextRowSetPaletteBank(7, 0x0E, 3, 0x1A);
        TextRowSetPaletteBank(8, 0x0E, 3, 0x1A);
    }
    else if (gUnk_03000678 == 2)
    {
        TextRowSetPaletteBank(9, 0x0E, 3, 0x1A);
        TextRowSetPaletteBank(10, 0x0E, 3, 0x1A);
    }
}


