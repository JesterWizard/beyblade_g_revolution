#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802fa94
// Draw the three visible rows of the gData_03000278 item list: name
// (highlighted row = cursor), a per-language category label for kinds 2/3
// (sub_0803DD88 name for kind 1) and the count; empty rows get the
// gData_08096B5C placeholder.

void sub_0802FA94(void)
{
    s32 i;
    u8 *buf;
    s32 name;

    TextGetAreaWidth();
    buf = BtlObjTableAdd(0x10);
    for (i = 0; i <= 2; i++)
    {
        if (gData_03000278->items[gData_03000278->top + i].count > 0)
        {
            TextSetCursor(0, i * 16 + 0x40);
            if (i == gData_03000278->cursor)
            {
                name = _08056428(gData_03000278->items[gData_03000278->top + i].kind, gData_03000278->items[gData_03000278->top + i].id);
                if (name != 0)
                    sub_08070AD4((struct Unk7069C *)gData_03000278->text, (void *)name, 15);
                else if (gData_03000278->items[gData_03000278->top + i].name != NULL)
                    sub_08070AD4((struct Unk7069C *)gData_03000278->text, gData_03000278->items[gData_03000278->top + i].name, 15);
                TextSetPaletteBank(14);
                TextRowSetPaletteBank((u16)(i * 2 + 12), 14, 2, 0x1B);
                TextRowSetPaletteBank((u16)(i * 2 + 13), 14, 2, 0x1B);
            }
            else
            {
                TextSetPaletteBank(15);
                TextRowSetPaletteBank((u16)(i * 2 + 12), 15, 2, 0x1B);
                TextRowSetPaletteBank((u16)(i * 2 + 13), 15, 2, 0x1B);
            }
            switch (gData_03000278->items[gData_03000278->top + i].kind)
            {
            case 2:
                switch (gData_03000278->items[gData_03000278->top + i].id)
                {
                case 4:
                    TextDrawAlign(gData_080970D4[gData_03000198->unk1818], 0x0C, 2);
                    break;
                case 3:
                    TextDrawAlign(gData_080970E8[gData_03000198->unk1818], 0x0C, 2);
                    break;
                case 2:
                    TextDrawAlign(gData_080970FC[gData_03000198->unk1818], 0x0C, 2);
                    break;
                case 1:
                    TextDrawAlign(gData_08097110[gData_03000198->unk1818], 0x0C, 2);
                    break;
                }
                break;
            case 3:
                switch (gData_03000278->items[gData_03000278->top + i].id)
                {
                case 4:
                    TextDrawAlign(gData_08097084[gData_03000198->unk1818], 0x0C, 2);
                    break;
                case 3:
                    TextDrawAlign(gData_08097098[gData_03000198->unk1818], 0x0C, 2);
                    break;
                case 2:
                    TextDrawAlign(gData_080970AC[gData_03000198->unk1818], 0x0C, 2);
                    break;
                case 1:
                    TextDrawAlign(gData_080970C0[gData_03000198->unk1818], 0x0C, 2);
                    break;
                }
                break;
            case 1:
                TextDrawAlign((void *)sub_0803DD88(gData_03000278->items[gData_03000278->top + i].id), 0x0C, 2);
                break;
            }
            if (gData_03000278->top + i < gData_03000278->count - 1)
            {
                sub_080731F4(buf);
                TextFormatInt(gData_03000278->items[gData_03000278->top + i].count, buf, 0x10);
                TextDrawAlign(buf, 0xD4, 1);
            }
        }
        else
        {
            if (i == gData_03000278->cursor)
            {
                TextSetPaletteBank(14);
                TextRowSetPaletteBank((u16)(i * 2 + 12), 14, 2, 0x1B);
                TextRowSetPaletteBank((u16)(i * 2 + 13), 14, 2, 0x1B);
            }
            else
            {
                TextSetPaletteBank(15);
                TextRowSetPaletteBank((u16)(i * 2 + 12), 15, 2, 0x1B);
                TextRowSetPaletteBank((u16)(i * 2 + 13), 15, 2, 0x1B);
            }
            TextSetCursor(0, i * 16 + 0x40);
            TextDrawAlign(gData_08096B5C[gData_03000198->unk1818], 0x0C, 2);
        }
    }
    BtlObjTableRemove(buf);
}

