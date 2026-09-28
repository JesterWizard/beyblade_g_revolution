#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08056ba4
// Redraws the eight visible rows of a numbered list (label + number, plus a
// separator and name for valid ids),
// highlights the selected row and shows its icon sprite.
void sub_08056BA4(void *arg)
{
    struct Unk65560 *a = arg;
    u8 *line;
    u8 *num;
    struct Unk4FFCCIcon *icon;
    s32 i;

    line = StringAlloc(0x80);
    num = StringAlloc(0x80);
    icon = NULL;
    if (gData_0300066C == 0)
        return;
    if (a->unk274[4] != NULL)
    {
        BtlObjPoolFree(a->unk274[4]);
        a->unk274[4] = (struct Sprite *)icon;
    }
    for (i = 0; i < 8; i++)
    {
        TextSetCursor(0, i * 8 + 0x10);
        StringCopy(gData_08097430[gData_03000198->language], line, 0x80);
        TextFormatInt(gData_03000674 + i + 1, num, 0x80);
        StringAppend(num, line, 0x80);
        if (gData_03000710[gData_03000674 + i] >= 0)
        {
            StringAppend((const u8 *)0x083A89E0, line, 0x80);
            StringAppend((const u8 *)GetBeybladeNameWithIndex(gData_03000710[gData_03000674 + i]), line, 0x80);
        }
        TextDrawAlign(line, 0x4A, 2);
        if (i == gData_03000678)
        {
            TextRowSetPaletteBank((u16)(i + 6), 0xE, 0xA, 0x1A);
            DebugPrint((void *)0x083A89E4, gData_03000710[gData_03000674 + i]);
            icon = GetBeybladeWithIndex(gData_03000710[gData_03000674 + i]);
            if (icon != NULL)
            {
                a->unk274[4] = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(a->unk274[4], icon->unk14, 0x1800, 0x4000, 1, 0, 0, 2);
                ((void (*)(const void *, void *, u32))gData_080BB8C0[0])(icon->unk18, (void *)0x050003E0, 0x20);
                TextEntrySetPaletteBank(a->unk274[4], 15);
            }
        }
        else
        {
            TextRowSetPaletteBank((u16)(i + 6), 0xF, 0xA, 0x1A);
        }
    }
    StringFree(num);
    StringFree(line);
}

