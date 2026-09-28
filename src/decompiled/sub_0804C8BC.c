#include "global.h"
#include "ram_map.h"

// Redraws the five visible list rows: label text, highlight palette for the
// selected row, and a fresh icon sprite + palette per non-empty row.
void sub_0804C8BC(void *arg)
{
    struct Unk65560 *a = arg;
    s32 i;
    s32 y;
    u16 *pal;

    pal = (u16 *)0x05000360;
    for (i = 0; i < 5; i++)
    {
        if (a->unk274[i] != NULL)
        {
            BtlObjPoolFree(a->unk274[i]);
            a->unk274[i] = NULL;
        }
        if (gData_080989F0[gData_03000688 + i].unk00 >= 0)
        {
            TextSetCursor(0, i * 16 + 0x18);
            TextDrawAlign(gData_080989F0[gData_03000688 + i].unk04, 0x1C, 2);
            if (i == gData_03000684)
            {
                TextRowSetPaletteBank((u16)(i * 2 + 7), 0xE, 4, 0x17);
                TextRowSetPaletteBank((u16)(i * 2 + 8), 0xE, 4, 0x17);
            }
            else
            {
                TextRowSetPaletteBank((u16)(i * 2 + 7), 0xF, 4, 0x17);
                TextRowSetPaletteBank((u16)(i * 2 + 8), 0xF, 4, 0x17);
            }
            a->unk274[i] = BtlObjPoolAlloc(0);
            SpriteInitFromTemplate(a->unk274[i], gData_080989D8[gData_03000688 + i], 0xC400, (i * 16 + 0x38) << 8, 0, 0, 0, 0);
            TextEntrySetPaletteBank(a->unk274[i], (u8)(i + 11));
            ((void (*)(const void *, void *, u32))gData_080BB8C0[0])(gData_080989E4[gData_03000688 + i], pal, 0x20);
        }
        pal += 0x10;
    }
}
