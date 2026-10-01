#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802ecd8
/* match-compiler: old_agbcc */
// Built against an (s8, s8, s32) prototype of sub_0802E2F8; its definition
// takes (u16, u16, s32).
#define sub_0802E2F8(a, b, c) ((s32 (*)(s32, s32, s32))sub_0802E2F8)(a, b, c)

// Draw the three visible rows of the gData_03000278 list: name (highlighted
// with palette 14 on the cursor row, else 15) and, for all but the last
// entry, its right-aligned value from sub_0802E2F8.
void sub_0802ECD8(void)
{
    s32 i;
    u8 *buf;
    s32 name;
    s32 value;
    struct Unk8D0 *rec;
    struct CollectionLookup info;

    TextGetAreaWidth();
    buf = StringAlloc(0x10);
    for (i = 0; i <= 2; i++)
    {
        if (gData_03000278->entries[gData_03000278->top + i].unk0C < 0)
            continue;
        TextSetCursor(0, i * 16 + 0x40);
        if (i == gData_03000278->cursor)
        {
            name = _080563A8(gData_03000278->entries[gData_03000278->top + i].unk0D, gData_03000278->entries[gData_03000278->top + i].unk0C);
            if (name != 0)
                TextGroupSetString((struct TextGroup *)gData_03000278->text, (void *)name, 15);
            else
                TextGroupSetString((struct TextGroup *)gData_03000278->text, gData_03000278->entries[gData_03000278->top + i].name, 15);
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
        if (gData_03000278->top + i < gData_03000278->count - 1)
        {
            StringClear(buf);
            if ((u8)gData_03000278->entries[gData_03000278->top + i].unk0D == 1)
            {
                rec = CollectionFindEntry(gData_03000278->entries[gData_03000278->top + i].unk0C, gData_03000278->entries[gData_03000278->top + i].unk0E);
                value = sub_0802E2F8(gData_03000278->entries[gData_03000278->top + i].unk0D,
                                     gData_03000278->entries[gData_03000278->top + i].unk0C, 100 - rec->unk24);
            }
            else
            {
                struct Unk2ECD8Entry *e = &gData_03000278->entries[gData_03000278->top + i];
                s32 kind = e->unk0D;
                s32 id = e->unk0C;

                sub_0802C4A4(kind, e->unk0E, &info);
                value = sub_0802E2F8(kind, id, (s8)info.value);
            }
            TextFormatInt(value, buf, 0x10);
            TextDrawAlign(buf, 0xD4, 1);
        }
        TextDrawAlign(gData_03000278->entries[gData_03000278->top + i].name, 0x0C, 2);
    }
    StringFree(buf);
}

