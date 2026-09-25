#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

// @ 0x08039bd4
// Rebuilds the eight-row part menu. Each row is 16 bytes at gUnk_0300040C,
// indexed from gUnk_03000400. The row whose index equals gUnk_03000404 is
// drawn in full; the others only refresh the label and the cursor bar.

extern struct Unk39BD4Part *sub_0803E1F4(s32 id, s32 slot);
extern s32 sub_0803DDD8(s32 id);
extern s32 sub_0803DDB0(s32 id);
extern u32 gData_081146E4[];
extern u32 gData_080F3C9C[];
extern u32 gData_08114950[];
extern u32 gData_081155BC[];
extern u32 gData_08113B80[];

#define OBJ_PALETTE_3E0 0x050003E0u
#define MENU_ROW(i) ((struct Unk39BD4Row *)((u8 *)*(volatile u32 *)gUnk_0300040C + (((*(volatile s32 *)gUnk_03000400 + (i)) << 4))))

void sub_08039BD4(struct Unk39BD4 *screen)
{
    s32 rowIndex;
    s32 cursorY;
    struct Unk39BD4Row *row;
    s32 kind;
    s32 rowId;
    struct Unk705DC *text;

    sub_08061784();
    if (screen->unk284 != 0)
    {
        sub_0806FE84(screen->unk284);
        screen->unk284 = 0;
    }
    if (screen->unk288 != 0)
    {
        sub_0806FE84(screen->unk288);
        screen->unk288 = 0;
    }
    if (screen->unk28C != 0)
    {
        sub_0806FE84(screen->unk28C);
        screen->unk28C = 0;
    }
    if (screen->unk290 != 0)
    {
        sub_0806FE84(screen->unk290);
        screen->unk290 = 0;
    }
    if (screen->unk294 != 0)
    {
        sub_0806FE84(screen->unk294);
        screen->unk294 = 0;
    }
    if (screen->unk298 != 0)
    {
        sub_0806FE84(screen->unk298);
        screen->unk298 = 0;
    }
    if (screen->unk29C != 0)
    {
        sub_0806FE84(screen->unk29C);
        screen->unk29C = 0;
    }
    if (screen->unk2A0 != 0)
    {
        sub_0806FE84(screen->unk2A0);
        screen->unk2A0 = 0;
    }
    if (screen->unk2B0 != 0)
    {
        sub_0806FE84(screen->unk2B0);
        screen->unk2B0 = 0;
    }

    cursorY = 0x10;
    for (rowIndex = 0; rowIndex < 8; rowIndex++)
    {
        row = &(*(struct Unk39BD4Row **)gUnk_0300040C)[*(s32 *)gUnk_03000400 + rowIndex];
        rowId = row->unk0C;
        if (rowId < 0)
        {
            cursorY += 8;
            continue;
        }

        kind = row->unk0D;
        if (rowIndex == *(s32 *)gUnk_03000404 && kind == 1)
        {
            struct Unk39BD4Part *part;

            part = sub_0803E1F4(rowId, row->unk0E);
            if (part != 0)
            {
                text = sub_0806FDD0(0);
                screen->unk284 = text;
                sub_0806FF58(text, (void *)part->unk14, 0x1800, 0x4000, kind, 0, 0, 2);
                _08073C4C((void *)part->unk18, (void *)OBJ_PALETTE_3E0, 0x20, (void *)gData_080BB8C0[0]);
                sub_080705DC(screen->unk284, 0x0F);

                text = sub_0806FDD0(0);
                screen->unk298 = text;
                sub_0806FF58(text, gData_081146E4, 0x1800, 0x8400, kind, 0, 0, (u16)sub_0803E328((struct Unk3E328 *)part));

                text = sub_0806FDD0(0);
                screen->unk29C = text;
                sub_0806FF58(text, gData_081146E4, 0x1800, 0x8D00, kind, 0, 0, (u16)sub_0803E374((struct Unk3E328 *)part));

                text = sub_0806FDD0(0);
                screen->unk2A0 = text;
                sub_0806FF58(text, gData_081146E4, 0x1800, 0x9600, kind, 0, 0, (u16)sub_0803E3C0((struct Unk3E328 *)part));
                sub_080705DC(screen->unk298, 0x0E);
                sub_080705DC(screen->unk29C, 0x0E);
                sub_080705DC(screen->unk2A0, 0x0E);

                text = sub_0806FDD0(0);
                screen->unk28C = text;
                sub_0806FF58(text, gData_080F3C9C, 0x800, 0x2400, kind, 0, 0, (u16)part->unk24);
                text->unk18 = sub_08031124(part->unk24, 0x64, 0xB6);
                sub_080705DC(text, 0x0E);

                text = sub_0806FDD0(0);
                screen->unk294 = text;
                sub_0806FF58(text, gData_08114950, 0x800, 0x6F00, kind, 0, 0, 0);
                text->unk18 = _0803DE00(part);
                sub_080705DC(text, 0x0E);

                text = sub_0806FDD0(0);
                screen->unk290 = text;
                sub_0806FF58(text, gData_081155BC, 0x700, 0x8100, kind, 0, 0, gMainWorkPtr->unk1818);
                sub_080705DC(text, 0x0E);
            }
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)row->unk04, 0x42, 2);
            sub_08061D68((u16)(rowIndex + 6), 0x0E, 9, 0x1A);
        }
        else if (rowIndex == *(s32 *)gUnk_03000404 && kind == 2)
        {
            text = sub_0806FDD0(0);
            screen->unk2B0 = text;
            sub_0806FF58(text, gData_080F3C9C, 0x800, 0x2400, 1, 0, 0, 0);
            text->unk18 = sub_08031124(0x64 - (s8)gMainWorkPtr->unk1694[row->unk0E].unk02, 0x64, 0xB6);
            _08073C4C(gData_08113B80, (void *)OBJ_PALETTE_3E0, 0x20, (void *)gData_080BB8C0[0]);
            sub_080705DC(text, 0x0F);

            text = sub_0806FDD0(0);
            screen->unk2A0 = text;
            sub_0806FF58(text, (void *)((struct Unk39BD4Row *)((u8 *)*(u32 *)gUnk_0300040C + ((*(volatile s32 *)gUnk_03000400 + rowIndex) << 4)))->unk08, 0x2000, 0x4800, 1, 0, 0, 0);
            sub_080705DC(text, 0x0E);
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)sub_0803DDD8(row->unk0C), 0x42, 2);
            sub_08061D68((u16)(rowIndex + 6), 0x0E, 9, 0x1A);
        }
        else if (rowIndex == *(s32 *)gUnk_03000404 && kind == 3)
        {
            text = sub_0806FDD0(0);
            screen->unk2B0 = text;
            sub_0806FF58(text, gData_080F3C9C, 0x800, 0x2400, 1, 0, 0, 0);
            text->unk18 = sub_08031124(0x64 - (s8)gMainWorkPtr->unk1694[row->unk0E].unk02, 0x64, 0xB6);
            _08073C4C(gData_08113B80, (void *)OBJ_PALETTE_3E0, 0x20, (void *)gData_080BB8C0[0]);
            sub_080705DC(text, 0x0F);

            text = sub_0806FDD0(0);
            screen->unk2A0 = text;
            sub_0806FF58(text, (void *)row->unk08, 0x2000, 0x4800, 1, 0, 0, 0);
            sub_080705DC(text, 0x0E);
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)sub_0803DDB0(row->unk0C), 0x42, 2);
            sub_08061D68((u16)(rowIndex + 6), 0x0E, 9, 0x1A);
        }
        else if (rowIndex != *(s32 *)gUnk_03000404 && kind == 1)
        {
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)row->unk04, 0x42, 2);
            sub_08061D68((u16)(rowIndex + 6), 0x0F, 9, 0x1A);
        }
        else if (rowIndex != *(s32 *)gUnk_03000404 && kind == 2)
        {
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)sub_0803DDD8(row->unk0C), 0x42, 2);
            sub_08061D68((u16)(rowIndex + 6), 0x0F, 9, 0x1A);
        }
        else if (rowIndex != *(s32 *)gUnk_03000404 && kind == 3)
        {
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)sub_0803DDB0(row->unk0C), 0x42, 2);
            sub_08061D68((u16)(rowIndex + 6), 0x0F, 9, 0x1A);
        }
        else if (rowIndex == *(s32 *)gUnk_03000404)
            sub_08061D68((u16)(rowIndex + 6), 0x0E, 9, 0x1A);
        else
            sub_08061D68((u16)(rowIndex + 6), 0x0F, 9, 0x1A);
        cursorY += 8;
    }
}
