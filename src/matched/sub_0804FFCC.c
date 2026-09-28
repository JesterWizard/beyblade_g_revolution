#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804ffcc
// Draw the detail panel for the selected list row: five text fields (with
// language-table fallbacks), the sub_0803E2AC category string, the record's
// unk26 counter, then rebuild the panel's six sprites from the row's record.
void DetailPanelDraw(struct Unk4FFCC *panel)
{
    struct Unk3E328 *rec;
    u8 *buf;
    void *text;
    void **strings;

    if (gData_030006BC[gData_030006AC + gData_030006B0].unk0C < 0)
        return;
    rec = sub_0803E1F4(gData_030006BC[gData_030006AC + gData_030006B0].unk0C, gData_030006BC[gData_030006AC + gData_030006B0].unk0E);
    buf = BtlObjTableAdd(8);
    TextGroupSetString(&gData_030006B4->unk60, (void *)sub_0803DD88(gData_030006BC[gData_030006AC + gData_030006B0].unk0C), 13);
    TextSetActiveObject((struct Unk617C4 *)0x082C44A8, (u32)gData_080B7258);
    TextSetCursor(0, 0x10);
    if ((text = (void *)_080505AC(gData_030006BC[gData_030006AC + gData_030006B0].unk0C, gData_030006BC[gData_030006AC + gData_030006B0].unk0E, 3)) == NULL)
    {
        strings = ((void **)gData_08097458);
        TextDrawAlign(strings[gData_03000198->unk1818], 0x10, 2);
    }
    else
        TextDrawAlign(text, 0xC0, 1);
    TextSetCursor(0, 0x20);
    if ((text = (void *)_080505AC(gData_030006BC[gData_030006AC + gData_030006B0].unk0C, gData_030006BC[gData_030006AC + gData_030006B0].unk0E, 0)) == NULL)
    {
        strings = ((void **)gData_08097458);
        TextDrawAlign(strings[gData_03000198->unk1818], 0x10, 2);
    }
    else
        TextDrawAlign(text, 0xC0, 1);
    TextSetCursor(0, 0x50);
    if ((text = (void *)_080505AC(gData_030006BC[gData_030006AC + gData_030006B0].unk0C, gData_030006BC[gData_030006AC + gData_030006B0].unk0E, 1)) == NULL)
    {
        strings = ((void **)gData_08097458);
        TextDrawAlign(strings[gData_03000198->unk1818], 0x10, 2);
    }
    else
        TextDrawAlign(text, 0xC0, 1);
    TextSetCursor(0, 0x30);
    if ((text = (void *)_080505AC(gData_030006BC[gData_030006AC + gData_030006B0].unk0C, gData_030006BC[gData_030006AC + gData_030006B0].unk0E, 2)) == NULL)
    {
        strings = ((void **)gData_08097458);
        TextDrawAlign(strings[gData_03000198->unk1818], 0x10, 2);
    }
    else
        TextDrawAlign(text, 0xC0, 1);
    TextSetCursor(0, 0x40);
    if ((text = (void *)_080505AC(gData_030006BC[gData_030006AC + gData_030006B0].unk0C, gData_030006BC[gData_030006AC + gData_030006B0].unk0E, 4)) == NULL)
    {
        strings = ((void **)gData_08097458);
        TextDrawAlign(strings[gData_03000198->unk1818], 0x10, 2);
    }
    else
        TextDrawAlign(text, 0xC0, 1);
    TextSetCursor(0, 0x30);
    switch (BeybladeGetType(rec))
    {
    case 0:
        strings = gData_080976EC;
        TextDrawAlign(strings[gData_03000198->unk1818], 0x0E, 2);
        break;
    case 1:
        strings = gData_08097700;
        TextDrawAlign(strings[gData_03000198->unk1818], 0x0E, 2);
        break;
    case 2:
        strings = gData_08097714;
        TextDrawAlign(strings[gData_03000198->unk1818], 0x0E, 2);
        break;
    case 3:
        strings = gData_08097728;
        TextDrawAlign(strings[gData_03000198->unk1818], 0x0E, 2);
        break;
    }
    if (rec != NULL)
    {
        if (rec->unk21 == -1)
            TextFormatInt(0, buf, 8);
        else
        {
            if (rec->unk26 < 0)
                rec->unk26 = 0;
            TextFormatInt(rec->unk26, buf, 8);
        }
    }
    TextSetCursor(0, 0x10);
    TextDrawAlign(buf, 0x30, 2);
    sub_080507B8((u8 *)panel);
    VBlankIntrWait();
    if (panel->unk28C[0] != NULL)
    {
        BtlObjPoolFree(panel->unk28C[0]);
        panel->unk28C[0] = NULL;
    }
    if (panel->unk28C[1] != NULL)
    {
        BtlObjPoolFree(panel->unk28C[1]);
        panel->unk28C[1] = NULL;
    }
    if (panel->unk28C[2] != NULL)
    {
        BtlObjPoolFree(panel->unk28C[2]);
        panel->unk28C[2] = NULL;
    }
    if (panel->unk28C[3] != NULL)
    {
        BtlObjPoolFree(panel->unk28C[3]);
        panel->unk28C[3] = NULL;
    }
    if (panel->unk28C[4] != NULL)
    {
        BtlObjPoolFree(panel->unk28C[4]);
        panel->unk28C[4] = NULL;
    }
    if (panel->unk28C[5] != NULL)
    {
        BtlObjPoolFree(panel->unk28C[5]);
        panel->unk28C[5] = NULL;
    }
    panel->unk28C[1] = BtlObjPoolAlloc(0);
    SpriteInitFromTemplate(panel->unk28C[1], (struct Unk6FF58Src *)0x08114950, 0xA300, 0xE00, 1, 0, 0, 0);
    panel->unk28C[1]->unk18 = _0803DE00(rec);
    TextEntrySetPaletteBank(panel->unk28C[1], 14);
    panel->unk28C[2] = BtlObjPoolAlloc(0);
    SpriteInitFromTemplate(panel->unk28C[2], (struct Unk6FF58Src *)0x080F3C9C, 0xE00, 0x1600, 1, 0, 0, 0);
    TextEntrySetPaletteBank(panel->unk28C[2], 14);
    panel->unk28C[2]->unk18 = ScaleRatio(rec->unk24, 100, 0xB6);
    panel->unk28C[3] = BtlObjPoolAlloc(0);
    SpriteInitFromTemplate(panel->unk28C[3], (struct Unk6FF58Src *)0x081146E4, 0x2A00, 0x5F00, 1, 0, 0, BeybladeAttackRating(rec));
    panel->unk28C[4] = BtlObjPoolAlloc(0);
    SpriteInitFromTemplate(panel->unk28C[4], (struct Unk6FF58Src *)0x081146E4, 0x2A00, 0x6700, 1, 0, 0, BeybladeDefenseRating(rec));
    panel->unk28C[5] = BtlObjPoolAlloc(0);
    SpriteInitFromTemplate(panel->unk28C[5], (struct Unk6FF58Src *)0x081146E4, 0x2A00, 0x6F00, 1, 0, 0, BeybladeEnduranceRating(rec));
    TextEntrySetPaletteBank(panel->unk28C[3], 14);
    TextEntrySetPaletteBank(panel->unk28C[4], 14);
    TextEntrySetPaletteBank(panel->unk28C[5], 14);
    /* rec is reused for the icon entry (one variable in the original). */
    rec = sub_0803DCFC(gData_030006BC[gData_030006AC + gData_030006B0].unk0C);
    if (rec != NULL)
    {
        panel->unk28C[0] = BtlObjPoolAlloc(0);
        SpriteInitFromTemplate(panel->unk28C[0], ((struct Unk4FFCCIcon *)rec)->unk14, 0x1400, 0x2800, 0, 0, 0, 2);
        TextEntrySetPaletteBank(panel->unk28C[0], 15);
        ((void (*)(const void *, void *, u32))gData_080BB8C0[0])(((struct Unk4FFCCIcon *)rec)->unk18, (void *)0x050003E0, 0x20);
    }
    BtlObjTableRemove(buf);
}

