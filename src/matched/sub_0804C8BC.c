#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

// @ 0x0804c8bc
// Redraw the five visible list rows from gData_080989F0: free each row icon,
// then for valid rows (id >= 0) draw the label, highlight the cursor row and
// rebuild the icon sprite plus its palette.
void sub_0804C8BC(void *arg)
{
    struct Unk4BD38 *a = arg;
    s32 i;
    u16 *pal;

    i = 0;
    pal = (u16 *)0x05000360;
    for (i = 0; i < 5; i++)
    {
        if (a->unk274[i])
        {
            BtlObjPoolFree(a->unk274[i]);
            a->unk274[i] = NULL;
        }
        if (gData_080989F0[gData_03000688 + i].unk00 > -1)
        {
            TextSetCursor(0, i * 16 + 0x18);
            TextDrawAlign(gData_080989F0[gData_03000688 + i].unk04, 0x1C, 2);
            if (i == gData_03000684)
            {
                TextRowSetPaletteBank((u16)(2 * i + 7), 0x0E, 4, 0x17);
                TextRowSetPaletteBank((u16)((i + 4) * 2), 0x0E, 4, 0x17);
            }
            else
            {
                TextRowSetPaletteBank((u16)(2 * i + 7), 0x0F, 4, 0x17);
                TextRowSetPaletteBank((u16)((i + 4) * 2), 0x0F, 4, 0x17);
            }
            a->unk274[i] = BtlObjPoolAlloc(0);
            SpriteInitFromTemplate(a->unk274[i], gData_080989D8[gData_03000688 + i], 0xC400, ((i << 4) + 0x38) << 8, 0, 0, 0, 0);
            TextEntrySetPaletteBank(a->unk274[i], (u8)(i + 11));
            ((void (*)(void *, void *, u32))gData_080BB8C0[0])(gData_080989E4[gData_03000688 + i], pal, 0x20);
        }
        pal += 0x10;
    }
}

