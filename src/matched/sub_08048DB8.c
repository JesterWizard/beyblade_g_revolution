#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08048db8
// Detail panel for the selected Beyblade: name, Bit-Beast EXP, and two
// icon-derived labels, then its sprite (palette 15) and icon (palette 13).
void sub_08048DB8(void *arg)
{
    struct Unk65560 *a = arg;
    u8 *buf;
    struct Unk42E78 *entry;
    struct Unk4FFCCIcon *icon;

    buf = BtlObjTableAdd(0x10);
    entry = BeybladeCollectionEntry(gData_03000648[a->unk2D5]);
    if (gData_0300064C > 0)
    {
        icon = sub_0803DCFC(entry->unk05);
        TextSetCursor(0, 0x18);
        TextDrawAlign(sub_08042B00(gData_03000648[a->unk2D5]), 0x4A, 2);
        TextSetCursor(0, 0x28);
        TextFormatInt(entry->bitBeastExp, buf, 0x10);
        TextDrawAlign(buf, 0x4A, 2);
        TextSetCursor(0, 0x38);
        TextDrawAlign((void *)sub_0803DD88(entry->unk05), 0x4A, 2);
        TextSetCursor(0, 0x48);
        TextDrawAlign((void *)sub_0803DBD0(icon->unk21), 0x4A, 2);
        if (a->unk274[4] != NULL)
        {
            BtlObjPoolFree(a->unk274[4]);
            a->unk274[4] = NULL;
        }
        if (a->unk274[5] != NULL)
        {
            BtlObjPoolFree(a->unk274[5]);
            a->unk274[5] = NULL;
        }
        a->unk274[4] = BtlObjPoolAlloc(0);
        SpriteInitFromTemplate(a->unk274[4], sub_08042B28(gData_03000648[a->unk2D5]), 0x800, 0x1000, 1, 0, 0, 0);
        ((void (*)(const void *, void *, u32))gData_080BB8C0[0])(sub_08042B50(gData_03000648[a->unk2D5]), (void *)0x050003E0, 0x20);
        TextEntrySetPaletteBank(a->unk274[4], 15);
        if (icon != NULL)
        {
            a->unk274[5] = BtlObjPoolAlloc(0);
            SpriteInitFromTemplate(a->unk274[5], icon->unk14, 0x1800, 0x4000, 1, 0, 0, 2);
            ((void (*)(const void *, void *, u32))gData_080BB8C0[0])(icon->unk18, (void *)0x050003A0, 0x20);
            TextEntrySetPaletteBank(a->unk274[5], 13);
        }
    }
    BtlObjTableRemove(buf);
}

