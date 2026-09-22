#include "global.h"

struct Unk2FA94Record
{
    s32 unk00;
    s32 unk04;
    s32 unk08;
    void *unk0C;
};

struct Unk2FA94Root
{
    u8 filler_00[8];
    struct Unk2FA94Record *records;
    u8 filler_0C[0x124];
    s32 unk130;
    s32 unk134;
    s32 unk138;
};

void sub_0802FA94(void)
{
    struct Unk2FA94Root **root_loc;
    struct MainWork **main_loc;
    struct Unk2FA94Record *record;
    void *buffer;
    s32 i;
    s32 base;
    u32 step;
    u32 x;
    u32 y;
    s32 result;
    void *table;
    u8 table_index;

    TextGetAreaWidth();
    buffer = BtlObjTableAdd(0x10);
    i = 0;
    root_loc = (struct Unk2FA94Root **)gUnk_03000278;
    main_loc = gMainWorkPtrLoc;
    step = 0x40;
    y = 0xD000;
    x = 0xC000;
    do
    {
        base = (*root_loc)->unk134 + i;
        record = (*root_loc)->records + base;
        if (record->unk08 > 0)
        {
            TextSetCursor(0, step);
            if (i == (*root_loc)->unk138)
            {
                result = _08056428(record->unk04, record->unk00);
                if (result != 0)
                    sub_08070AD4(
                        (struct Unk7069C *)((u8 *)*root_loc + 0xF8),
                        (void *)result, 0x0F);
                else if (record->unk0C != 0)
                    sub_08070AD4(
                        (struct Unk7069C *)((u8 *)*root_loc + 0xF8),
                        record->unk0C, 0x0F);
                TextSetPaletteBank(0x0E);
                TextRowSetPaletteBank(x >> 16, 0x0E, 2, 0x1B);
                TextRowSetPaletteBank(y >> 16, 0x0E, 2, 0x1B);
            }
            else
            {
                TextSetPaletteBank(0x0F);
                TextRowSetPaletteBank(x >> 16, 0x0F, 2, 0x1B);
                TextRowSetPaletteBank(y >> 16, 0x0F, 2, 0x1B);
            }
            if (record->unk04 == 1)
            {
                result = sub_0803DD88(record->unk00);
                TextDrawAlign((void *)result, 0x0C, 2);
            }
            else if (record->unk04 == 2 || record->unk04 == 3)
            {
                if (record->unk00 == 1)
                {
                    if (record->unk04 == 2)
                        table = (void *)0x08097110;
                    else
                        table = (void *)0x080970C0;
                }
                else if (record->unk00 == 2)
                {
                    if (record->unk04 == 2)
                        table = (void *)0x080970FC;
                    else
                        table = (void *)0x080970AC;
                }
                else if (record->unk00 == 3)
                {
                    if (record->unk04 == 2)
                        table = (void *)0x080970E8;
                    else
                        table = (void *)0x08097098;
                }
                else if (record->unk00 == 4)
                {
                    if (record->unk04 == 2)
                        table = (void *)0x080970D4;
                    else
                        table = (void *)0x08097084;
                }
                else
                    table = 0;
                if (table != 0)
                {
                    table_index = (*main_loc)->unk1818;
                    TextDrawAlign(
                        ((void **)table)[table_index], 0x0C, 2);
                }
            }
            if (base < (*root_loc)->unk130 - 1)
            {
                sub_080731F4((u8 *)buffer);
                record = (*root_loc)->records + base;
                result = record->unk08;
                TextFormatInt(result, buffer, 0x10);
                TextDrawAlign(buffer, 0xD4, 1);
            }
        }
        else
        {
            if (i == (*root_loc)->unk138)
            {
                TextSetPaletteBank(0x0E);
                TextRowSetPaletteBank(x >> 16, 0x0E, 2, 0x1B);
                TextRowSetPaletteBank(y >> 16, 0x0E, 2, 0x1B);
            }
            else
            {
                TextSetPaletteBank(0x0F);
                TextRowSetPaletteBank(x >> 16, 0x0F, 2, 0x1B);
                TextRowSetPaletteBank(y >> 16, 0x0F, 2, 0x1B);
            }
            TextSetCursor(0, step);
            table = (void *)0x08096B5C;
            table_index = (*main_loc)->unk1818;
            TextDrawAlign(
                ((void **)table)[table_index], 0x0C, 2);
        }
        x += 0x40000;
        y += 0x40000;
        step += 0x10;
        i++;
    } while (i <= 2);
    BtlObjTableRemove(buffer);
}
