#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08039bd4
// Row i of the visible window into the row table.
#define MENU_ROW(i) (&gData_0300040C[gData_03000400 + (i)])
// Copy routine in ROM, used here to load a 16-colour OBJ palette.
#define PALETTE_LOAD ((void (*)(const void *src, void *dst, u32 size))gData_080BB8C0[0])

// Rebuilds the eight visible rows of the part menu. Frees the screen's text
// slots, then redraws each row's label; the cursor row (gData_03000404) also
// gets its detail panel (kind 1: part stats; kinds 2/3: gauge and name).
void PartMenuRebuild(struct Unk39BD4 *screen)
{
    s32 i;
    s32 kind;
    struct Unk39BD4Part *part;

    TextGetAreaWidth();
    if (screen->unk284 != NULL)
    {
        BtlObjPoolFree(screen->unk284);
        screen->unk284 = NULL;
    }
    if (screen->unk288 != NULL)
    {
        BtlObjPoolFree(screen->unk288);
        screen->unk288 = NULL;
    }
    if (screen->unk28C != NULL)
    {
        BtlObjPoolFree(screen->unk28C);
        screen->unk28C = NULL;
    }
    if (screen->unk290 != NULL)
    {
        BtlObjPoolFree(screen->unk290);
        screen->unk290 = NULL;
    }
    if (screen->unk294 != NULL)
    {
        BtlObjPoolFree(screen->unk294);
        screen->unk294 = NULL;
    }
    if (screen->unk298 != NULL)
    {
        BtlObjPoolFree(screen->unk298);
        screen->unk298 = NULL;
    }
    if (screen->unk29C != NULL)
    {
        BtlObjPoolFree(screen->unk29C);
        screen->unk29C = NULL;
    }
    if (screen->unk2A0 != NULL)
    {
        BtlObjPoolFree(screen->unk2A0);
        screen->unk2A0 = NULL;
    }
    if (screen->unk2B0 != NULL)
    {
        BtlObjPoolFree(screen->unk2B0);
        screen->unk2B0 = NULL;
    }

    for (i = 0; i < 8; i++)
    {
        if (MENU_ROW(i)->unk0C < 0)
            continue;
        if (i == gData_03000404)
        {
            switch (kind = MENU_ROW(i)->unk0D)
            {
            case 1:
                part = sub_0803E1F4(MENU_ROW(i)->unk0C, MENU_ROW(i)->unk0E);
                if (part != NULL)
                {
                    screen->unk284 = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk284, (void *)part->unk14, 0x1800, 0x4000, kind, 0, 0, 2);
                    PALETTE_LOAD((void *)part->unk18, (void *)0x050003E0, 0x20);
                    TextEntrySetPaletteBank(screen->unk284, 0x0F);

                    screen->unk298 = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk298, (void *)0x081146E4, 0x1800, 0x8400, kind, 0, 0,
                        (u16)BeybladeAttackRating((struct Unk3E328 *)part));
                    screen->unk29C = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk29C, (void *)0x081146E4, 0x1800, 0x8D00, kind, 0, 0,
                        (u16)BeybladeDefenseRating((struct Unk3E328 *)part));
                    screen->unk2A0 = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk2A0, (void *)0x081146E4, 0x1800, 0x9600, kind, 0, 0,
                        (u16)BeybladeEnduranceRating((struct Unk3E328 *)part));
                    TextEntrySetPaletteBank(screen->unk298, 0x0E);
                    TextEntrySetPaletteBank(screen->unk29C, 0x0E);
                    TextEntrySetPaletteBank(screen->unk2A0, 0x0E);

                    screen->unk28C = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk28C, (void *)0x080F3C9C, 0x800, 0x2400, kind, 0, 0, (u16)part->unk24);
                    screen->unk28C->unk18 = ScaleRatio(part->unk24, 100, 0xB6);
                    TextEntrySetPaletteBank(screen->unk28C, 0x0E);

                    screen->unk294 = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk294, (void *)0x08114950, 0x800, 0x6F00, kind, 0, 0, 0);
                    screen->unk294->unk18 = _0803DE00(part);
                    TextEntrySetPaletteBank(screen->unk294, 0x0E);

                    screen->unk290 = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk290, (void *)0x081155BC, 0x700, 0x8100, kind, 0, 0, gMainWorkPtr->unk1818);
                    TextEntrySetPaletteBank(screen->unk290, 0x0E);
                }
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign((void *)MENU_ROW(i)->unk04, 0x42, 2);
                break;
            case 2:
                screen->unk2B0 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(screen->unk2B0, (void *)0x080F3C9C, 0x800, 0x2400, 1, 0, 0, 0);
                screen->unk2B0->unk18 = ScaleRatio(100 - (s8)gMainWorkPtr->unk1694[MENU_ROW(i)->unk0E].unk02, 100, 0xB6);
                PALETTE_LOAD((void *)0x08113B80, (void *)0x050003E0, 0x20);
                TextEntrySetPaletteBank(screen->unk2B0, 0x0F);
                screen->unk2A0 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(screen->unk2A0, (void *)MENU_ROW(i)->unk08, 0x2000, 0x4800, 1, 0, 0, 0);
                TextEntrySetPaletteBank(screen->unk2A0, 0x0E);
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign(sub_0803DDD8(MENU_ROW(i)->unk0C), 0x42, 2);
                break;
            case 3:
                screen->unk2B0 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(screen->unk2B0, (void *)0x080F3C9C, 0x800, 0x2400, 1, 0, 0, 0);
                screen->unk2B0->unk18 = ScaleRatio(100 - (s8)gMainWorkPtr->unk1694[MENU_ROW(i)->unk0E].unk02, 100, 0xB6);
                PALETTE_LOAD((void *)0x08113B80, (void *)0x050003E0, 0x20);
                TextEntrySetPaletteBank(screen->unk2B0, 0x0F);
                screen->unk2A0 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(screen->unk2A0, (void *)MENU_ROW(i)->unk08, 0x2000, 0x4800, 1, 0, 0, 0);
                TextEntrySetPaletteBank(screen->unk2A0, 0x0E);
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign(sub_0803DDB0(MENU_ROW(i)->unk0C), 0x42, 2);
                break;
            }
            TextRowSetPaletteBank((u16)(i + 6), 0x0E, 9, 0x1A);
        }
        else
        {
            switch (MENU_ROW(i)->unk0D)
            {
            case 1:
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign((void *)MENU_ROW(i)->unk04, 0x42, 2);
                break;
            case 2:
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign(sub_0803DDD8(MENU_ROW(i)->unk0C), 0x42, 2);
                break;
            case 3:
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign(sub_0803DDB0(MENU_ROW(i)->unk0C), 0x42, 2);
                break;
            }
            TextRowSetPaletteBank((u16)(i + 6), 0x0F, 9, 0x1A);
        }
    }
}

