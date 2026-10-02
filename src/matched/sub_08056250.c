#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x08056250
typedef void (*CpuCopyFunc)(const void *, void *, u32);

// Redraws the eight visible rows of the scrolling list: label text for each
// filled row, and for the cursor row an icon sprite plus its palette.
void ScrollListRedraw(struct Unk56250 *a)
{
    s32 i;

    TextGetAreaWidth();
    if (gData_0300066C == 0)
        return;
    if (a->unk284 != NULL)
    {
        BtlObjPoolFree(a->unk284);
        a->unk284 = NULL;
    }
    for (i = 0; i < 8; i++)
    {
        if (gData_03000664[gData_03000674 + i].unk0C > -1)
        {
            TextSetCursor(0, i * 8 + 0x10);
            TextDrawAlign(gData_03000664[gData_03000674 + i].unk04, 0x4A, 2);
            if (i == gData_03000678)
            {
                a->unk284 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(a->unk284, gData_03000664[gData_03000674 + i].unk08, 0x2000, 0x4800, 1, 0, 0, 0);
                TextEntrySetPaletteBank(a->unk284, 0x0F);
                ((CpuCopyFunc)gData_080BB8C0[0])(gData_080779A8[gData_03000664[gData_03000674 + i].unk0C], (void *)0x050003E0, 0x20);
                TextRowSetPaletteBank((u16)(i + 6), 0x0E, 0x0A, 0x1A);
            }
            else
            {
                TextRowSetPaletteBank((u16)(i + 6), 0x0F, 0x0A, 0x1A);
            }
        }
    }
}

