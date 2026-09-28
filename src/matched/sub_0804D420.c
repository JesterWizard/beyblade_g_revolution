#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804d420
// Frees the five list icon sprites, then redraws the five visible list rows,
// spawning the icon for the selected row and highlighting it with palette 14.
void sub_0804D420(void *arg)
{
    struct Unk65560 *a = arg;
    s32 i;
    struct Unk4FFCCIcon *icon = NULL;

    if (a->unk274[11] != NULL)
    {
        BtlObjPoolFree(a->unk274[11]);
        a->unk274[11] = NULL;
    }
    if (a->unk274[12] != NULL)
    {
        BtlObjPoolFree(a->unk274[12]);
        a->unk274[12] = NULL;
    }
    if (a->unk274[13] != NULL)
    {
        BtlObjPoolFree(a->unk274[13]);
        a->unk274[13] = NULL;
    }
    if (a->unk274[14] != NULL)
    {
        BtlObjPoolFree(a->unk274[14]);
        a->unk274[14] = NULL;
    }
    if (a->unk274[15] != NULL)
    {
        BtlObjPoolFree(a->unk274[15]);
        a->unk274[15] = NULL;
    }
    VBlankIntrWait();
    for (i = 0; i < 5; i++)
    {
        TextSetCursor(0, i * 16 + 0x18);
        TextDrawAlign((void *)sub_0803DD88((s16)gData_03000674 + i), 0x1C, 2);
        if (i == (s16)gData_03000678)
        {
            icon = sub_0803DCFC((s16)gData_03000674 + i);
            if (icon != NULL)
            {
                a->unk274[i + 11] = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(a->unk274[i + 11], icon->unk14, 0xA000, 0x800, 0, 0, 0, 2);
                TextEntrySetPaletteBank(a->unk274[i + 11], 15);
                ((void (*)(const void *, void *, u32))gData_080BB8C0[0])(icon->unk18, (void *)0x050003E0, 0x20);
            }
            TextRowSetPaletteBank((u16)(i * 2 + 7), 0xE, 4, 0x19);
            TextRowSetPaletteBank((u16)(i * 2 + 8), 0xE, 4, 0x19);
        }
        else
        {
            TextRowSetPaletteBank((u16)(i * 2 + 7), 0xF, 4, 0x19);
            TextRowSetPaletteBank((u16)(i * 2 + 8), 0xF, 4, 0x19);
        }
    }
}

