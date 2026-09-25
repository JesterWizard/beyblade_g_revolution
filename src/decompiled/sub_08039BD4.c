typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

struct Unk705DC {
    u8 filler_00[4];
    struct Unk705DC *unk04;
    u32 unk08;
    u32 unk0C;
    u32 unk10;
    u16 unk14;
    u16 unk16;
    u16 unk18;
};

struct Unk1694 {
    s8 unk00;
    u8 unk01;
    u8 unk02;
    s8 unk03;
};

struct MainWork {
    u8 filler_0000[0x1694];
    struct Unk1694 *unk1694;
    u8 filler_1698[0x180];
    u8 unk1818;
};

struct Unk39BD4Row {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    s8 unk0C;
    s8 unk0D;
    s8 unk0E;
    u8 unk0F;
};

struct Unk39BD4Part {
    u8 filler_00[0x14];
    u32 unk14;
    u32 unk18;
    u8 filler_1C[8];
    s8 unk24;
};

struct Unk39BD4 {
    u8 filler_000[0x284];
    struct Unk705DC *unk284;
    struct Unk705DC *unk288;
    struct Unk705DC *unk28C;
    struct Unk705DC *unk290;
    struct Unk705DC *unk294;
    struct Unk705DC *unk298;
    struct Unk705DC *unk29C;
    struct Unk705DC *unk2A0;
    u8 filler_2A4[0xC];
    struct Unk705DC *unk2B0;
};

struct Unk3E328 {
    u8 filler_00[0x1D];
    s8 unk1D;
};

#define gUnk_03000400 0x03000400
#define gUnk_03000404 0x03000404
#define gUnk_0300040C 0x0300040C
#define gMainWorkPtr (*(struct MainWork **)0x03000198)

extern u32 gData_080BB8C0[];
extern void sub_0806FF58(void *a, void *b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h);
extern void sub_0806FE84(void *a);
extern void *sub_0806FDD0(u16 a);
extern void sub_080705DC(struct Unk705DC *a, s32 b);
extern void _08073C4C(void *a, void *b, u32 c, void *d);
extern s16 _0803DE00(void *a);
extern s16 sub_08031124(s32 a, s32 b, s32 c);
extern void sub_08061784(void);
extern void sub_0806171C(void *a, u32 b, u32 c);
extern void sub_080615EC(u32 x, u32 y);
extern void sub_08061D68(u32 a, u32 b, u32 c, u32 d);
extern s32 sub_0803E328(struct Unk3E328 *a);
extern s32 sub_0803E374(struct Unk3E328 *a);
extern s32 sub_0803E3C0(struct Unk3E328 *a);

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
    s32 zero;
    s32 cursorY;
    struct Unk39BD4Row *row;
    s32 kind;
    s32 rowId;
    struct Unk705DC *text;
    struct Unk705DC *text29C;
    struct Unk705DC *text298;

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

    rowIndex = 0;
    zero = rowIndex;
    cursorY = 0x10;
    for (; rowIndex < 8; rowIndex++)

        {
        row = &(*(struct Unk39BD4Row **)gUnk_0300040C)[*(s32 *)gUnk_03000400 + rowIndex];
        rowId = row->unk0C;
        if (rowId < 0)
        {
            cursorY += 8;
            continue;
        }

        kind = row->unk0D;
        {
            u16 rowLabel;

            rowLabel = rowIndex + 6;
        if (rowIndex == *(s32 *)gUnk_03000404 && kind == 1)
        {
            struct Unk39BD4Part *part;

            part = sub_0803E1F4(rowId, row->unk0E);
            if (part != 0)
            {
                text = sub_0806FDD0(0);
                screen->unk284 = text;
                sub_0806FF58(text, (void *)part->unk14, 0x1800, 0x4000, kind, zero, zero, 2);
                _08073C4C((void *)part->unk18, (void *)OBJ_PALETTE_3E0, 0x20, (void *)gData_080BB8C0[0]);
                sub_080705DC(screen->unk284, 0x0F);

                text298 = sub_0806FDD0(0);
                screen->unk298 = text298;
                sub_0806FF58(text298, gData_081146E4, 0x1800, 0x8400, kind, zero, zero, (u16)sub_0803E328((struct Unk3E328 *)part));

                text29C = sub_0806FDD0(0);
                screen->unk29C = text29C;
                sub_0806FF58(text29C, gData_081146E4, 0x1800, 0x8D00, kind, zero, zero, (u16)sub_0803E374((struct Unk3E328 *)part));

                text = sub_0806FDD0(0);
                screen->unk2A0 = text;
                sub_0806FF58(text, gData_081146E4, 0x1800, 0x9600, kind, zero, zero, (u16)sub_0803E3C0((struct Unk3E328 *)part));
                sub_080705DC(text298, 0x0E);
                sub_080705DC(text29C, 0x0E);
                sub_080705DC(screen->unk2A0, 0x0E);

                text = sub_0806FDD0(0);
                screen->unk28C = text;
                { u16 stat; stat = (u16)part->unk24; sub_0806FF58(text, gData_080F3C9C, 0x800, 0x2400, kind, zero, zero, stat); }
                text->unk18 = sub_08031124(part->unk24, 0x64, 0xB6);
                sub_080705DC(text, 0x0E);

                text = sub_0806FDD0(0);
                screen->unk294 = text;
                sub_0806FF58(text, gData_08114950, 0x800, 0x6F00, kind, zero, zero, zero);
                text->unk18 = _0803DE00(part);
                sub_080705DC(text, 0x0E);

                text = sub_0806FDD0(0);
                screen->unk290 = text;
                sub_0806FF58(text, gData_081155BC, 0x700, 0x8100, kind, zero, zero, gMainWorkPtr->unk1818);
                sub_080705DC(text, 0x0E);
            }
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)row->unk04, 0x42, 2);
            sub_08061D68(rowLabel, 0x0E, 9, 0x1A);
        }
        else if (rowIndex == *(s32 *)gUnk_03000404 && kind == 2)
        {
            text = sub_0806FDD0(0);
            screen->unk2B0 = text;
            sub_0806FF58(text, gData_080F3C9C, 0x800, 0x2400, 1, zero, zero, zero);
            text->unk18 = sub_08031124(0x64 - (s8)gMainWorkPtr->unk1694[row->unk0E].unk02, 0x64, 0xB6);
            _08073C4C(gData_08113B80, (void *)OBJ_PALETTE_3E0, 0x20, (void *)gData_080BB8C0[0]);
            sub_080705DC(text, 0x0F);

            text = sub_0806FDD0(0);
            screen->unk2A0 = text;
            sub_0806FF58(text, (void *)((struct Unk39BD4Row *)((u8 *)*(u32 *)gUnk_0300040C + ((*(volatile s32 *)gUnk_03000400 + rowIndex) << 4)))->unk08, 0x2000, 0x4800, 1, zero, zero, zero);
            sub_080705DC(text, 0x0E);
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)sub_0803DDD8(row->unk0C), 0x42, 2);
            sub_08061D68(rowLabel, 0x0E, 9, 0x1A);
        }
        else if (rowIndex == *(s32 *)gUnk_03000404 && kind == 3)
        {
            text = sub_0806FDD0(0);
            screen->unk2B0 = text;
            sub_0806FF58(text, gData_080F3C9C, 0x800, 0x2400, 1, zero, zero, zero);
            text->unk18 = sub_08031124(0x64 - (s8)gMainWorkPtr->unk1694[row->unk0E].unk02, 0x64, 0xB6);
            _08073C4C(gData_08113B80, (void *)OBJ_PALETTE_3E0, 0x20, (void *)gData_080BB8C0[0]);
            sub_080705DC(text, 0x0F);

            text = sub_0806FDD0(0);
            screen->unk2A0 = text;
            sub_0806FF58(text, (void *)row->unk08, 0x2000, 0x4800, 1, zero, zero, zero);
            sub_080705DC(text, 0x0E);
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)sub_0803DDB0(row->unk0C), 0x42, 2);
            sub_08061D68(rowLabel, 0x0E, 9, 0x1A);
        }
        else if (rowIndex != *(s32 *)gUnk_03000404 && kind == 1)
        {
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)row->unk04, 0x42, 2);
            sub_08061D68(rowLabel, 0x0F, 9, 0x1A);
        }
        else if (rowIndex != *(s32 *)gUnk_03000404 && kind == 2)
        {
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)sub_0803DDD8(row->unk0C), 0x42, 2);
            sub_08061D68(rowLabel, 0x0F, 9, 0x1A);
        }
        else if (rowIndex != *(s32 *)gUnk_03000404 && kind == 3)
        {
            sub_080615EC(0, cursorY);
            row = MENU_ROW(rowIndex);
            sub_0806171C((void *)sub_0803DDB0(row->unk0C), 0x42, 2);
            sub_08061D68(rowLabel, 0x0F, 9, 0x1A);
        }
        else if (rowIndex == *(s32 *)gUnk_03000404)
            sub_08061D68(rowLabel, 0x0E, 9, 0x1A);
        else
            sub_08061D68(rowLabel, 0x0F, 9, 0x1A);
        }
        cursorY += 8;
    }
}