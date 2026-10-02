#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_08039BD4 */
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
                part = CollectionFindEntry(MENU_ROW(i)->unk0C, MENU_ROW(i)->unk0E);
                if (part != NULL)
                {
                    screen->unk284 = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk284, (void *)part->unk14, 0x1800, 0x4000, kind, 0, 0, 2);
                    PALETTE_LOAD((void *)part->unk18, (void *)0x050003E0, 0x20);
                    TextEntrySetPaletteBank(screen->unk284, 0x0F);

                    screen->unk298 = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk298, (void *)0x081146E4, 0x1800, 0x8400, kind, 0, 0,
                        (u16)BeybladeAttackRating((struct BeybladeBuild *)part));
                    screen->unk29C = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk29C, (void *)0x081146E4, 0x1800, 0x8D00, kind, 0, 0,
                        (u16)BeybladeDefenseRating((struct BeybladeBuild *)part));
                    screen->unk2A0 = BtlObjPoolAlloc(0);
                    SpriteInitFromTemplate(screen->unk2A0, (void *)0x081146E4, 0x1800, 0x9600, kind, 0, 0,
                        (u16)BeybladeEnduranceRating((struct BeybladeBuild *)part));
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
                    SpriteInitFromTemplate(screen->unk290, (void *)0x081155BC, 0x700, 0x8100, kind, 0, 0, gMainWorkPtr->language);
                    TextEntrySetPaletteBank(screen->unk290, 0x0E);
                }
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign((void *)MENU_ROW(i)->unk04, 0x42, 2);
                break;
            case 2:
                screen->unk2B0 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(screen->unk2B0, (void *)0x080F3C9C, 0x800, 0x2400, 1, 0, 0, 0);
                screen->unk2B0->unk18 = ScaleRatio(100 - (s8)gMainWorkPtr->unk1694[MENU_ROW(i)->unk0E].value, 100, 0xB6);
                PALETTE_LOAD((void *)0x08113B80, (void *)0x050003E0, 0x20);
                TextEntrySetPaletteBank(screen->unk2B0, 0x0F);
                screen->unk2A0 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(screen->unk2A0, (void *)MENU_ROW(i)->unk08, 0x2000, 0x4800, 1, 0, 0, 0);
                TextEntrySetPaletteBank(screen->unk2A0, 0x0E);
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign(RipcordNameGet(MENU_ROW(i)->unk0C), 0x42, 2);
                break;
            case 3:
                screen->unk2B0 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(screen->unk2B0, (void *)0x080F3C9C, 0x800, 0x2400, 1, 0, 0, 0);
                screen->unk2B0->unk18 = ScaleRatio(100 - (s8)gMainWorkPtr->unk1694[MENU_ROW(i)->unk0E].value, 100, 0xB6);
                PALETTE_LOAD((void *)0x08113B80, (void *)0x050003E0, 0x20);
                TextEntrySetPaletteBank(screen->unk2B0, 0x0F);
                screen->unk2A0 = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(screen->unk2A0, (void *)MENU_ROW(i)->unk08, 0x2000, 0x4800, 1, 0, 0, 0);
                TextEntrySetPaletteBank(screen->unk2A0, 0x0E);
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign(LauncherNameGet(MENU_ROW(i)->unk0C), 0x42, 2);
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
                TextDrawAlign(RipcordNameGet(MENU_ROW(i)->unk0C), 0x42, 2);
                break;
            case 3:
                TextSetCursor(0, i * 8 + 0x10);
                TextDrawAlign(LauncherNameGet(MENU_ROW(i)->unk0C), 0x42, 2);
                break;
            }
            TextRowSetPaletteBank((u16)(i + 6), 0x0F, 9, 0x1A);
        }
    }
}

/* fn: sub_08040F4C */
// @ 0x08040f4c
/* match-compiler: old_agbcc */
// Menu main loop: clear + set up the stack state, then per frame run the blend
// fade and dispatch on the mode byte until mode 3 ends the loop.
void MenuDispatchLoop(void)
{
    struct MenuState state;
    s32 done;

    done = 0;
    {
        u32 *src = gData_080BB8BC;
        _08073C4C(0, &state, sizeof(state), (void *)*src);
    }
    sub_0804109C(&state, MenuPageDefGet());
    WindowEffectCreate();
    sub_08060758();
    do
    {
        WindowRegsApply();
        BlendFadeTick();
        VBlankIntrWait();
        InputUpdate();
        if (!(state.unk324 & 1))
            _08073C40((void *)gData_080BB888[0]);
        if (state.unk2D7 == 1)
        {
            switch (state.unk322)
            {
            case 1:
                state.unk31C -= state.unk31E;
                if ((s16)state.unk31C < 0)
                {
                    state.unk31C = 0;
                    state.unk2D7 = 0;
                }
                break;
            case 2:
                state.unk31C += state.unk31E;
                if ((s16)state.unk31C > 0x1F)
                {
                    state.unk31C = 0x1F;
                    state.unk2D7 = 0;
                }
                break;
            }
            REG_BLDCNT = state.unk320;
            REG_BLDY = state.unk31C;
        }
        switch (state.unk2D4)
        {
        case 0:
            if (state.unk24C)
                _08073C44(&state, state.unk24C);
            break;
        case 1:
            if (state.unk250)
                _08073C44(&state, state.unk250);
            MenuDispatchKeyHandlers(&state);
            break;
        case 2:
            if (state.unk254)
                _08073C44(&state, state.unk254);
            break;
        case 3:
            done = 1;
            break;
        }
        if (state.unk258)
            _08073C44(&state, state.unk258);
    } while (!done);
    HeapFreeSlots8((struct Unk41394 *)&state);
    WindowEffectDestroy();
    sub_08060798();
}

/* fn: sub_080411EC */
// @ 0x080411ec
/* match-compiler: old_agbcc */
// Menu input dispatch: in mode 0 (repeat-filtered d-pad from sub_08045C5C)
// or mode 1 (raw held keys), run the first handler slot (unk25C..unk270 =
// right/left/up/down/A/B) whose key is down and which is set.
// The _08073C44/_08073C48 calls in retail are libgcc _call_via_rN thunks.
typedef void (*MenuHandler)(struct MenuState *);

void MenuDispatchKeyHandlers(void *arg)
{
    struct MenuState *a = arg;
    u32 flags;

    if (a->unk2D4 != 1)
        return;
    switch (a->unk2D9)
    {
    case 0:
        flags = sub_08045C5C(0x10, 8);
        if ((flags & 0x20) && a->onLeft != NULL)
            ((MenuHandler)a->onLeft)(a);
        else if ((flags & 0x10) && a->onRight != NULL)
            ((MenuHandler)a->onRight)(a);
        else if ((flags & 0x40) && a->onUp != NULL)
            ((MenuHandler)a->onUp)(a);
        else if ((flags & 0x80) && a->onDown != NULL)
            ((MenuHandler)a->onDown)(a);
        else if ((gData_03004060 & 1) && a->onButtonA != NULL)
            ((MenuHandler)a->onButtonA)(a);
        else if ((gData_03004060 & 2) && a->onButtonB != NULL)
            ((MenuHandler)a->onButtonB)(a);
        break;
    case 1:
        if ((gData_03004060 & 0x20) && a->onLeft != NULL)
            ((MenuHandler)a->onLeft)(a);
        else if ((gData_03004060 & 0x10) && a->onRight != NULL)
            ((MenuHandler)a->onRight)(a);
        else if ((gData_03004060 & 0x40) && a->onUp != NULL)
            ((MenuHandler)a->onUp)(a);
        else if ((gData_03004060 & 0x80) && a->onDown != NULL)
            ((MenuHandler)a->onDown)(a);
        else if ((gData_03004060 & 1) && a->onButtonA != NULL)
            ((MenuHandler)a->onButtonA)(a);
        else if ((gData_03004060 & 2) && a->onButtonB != NULL)
            ((MenuHandler)a->onButtonB)(a);
        break;
    }

}

/* fn: sub_08056250 */
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

/* fn: sub_08066390 */
// @ 0x08066390
void MenuPageSet(u8 v)
{
    *(u8 *)gUnk_03000964 = v;
}

/* fn: sub_0806639C */
// @ 0x0806639c
void *MenuPageDefGet(void)
{
    u32 tmp[2];
    void **base;
    s32 idx;

    tmp[0] = 0x080BA1A8;
    base = (void **)tmp[0];
    idx = (s8)*((u8 *)gUnk_03000964);
    idx <<= 2;
    return *((void **)(((u8 *)((void **)tmp[0])) + idx));
}

/* fn: sub_08066FB8 */
// @ 0x08066fb8
void MenuDrawThreeLineList(void)
{
    VBlankIntrWait();
    TextWindowPopState();
    TextRowSetPaletteBank(5, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(6, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(7, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(8, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(9, 0x0F, 3, 0x1A);
    TextRowSetPaletteBank(10, 0x0F, 3, 0x1A);
    VBlankIntrWait();

    TextSetCursor(0, 0x08);
    TextDrawAlign(gData_080BB110[gUnk_03000674].unk0C, TextGetAreaWidth() / 2, 0);
    TextSetCursor(0, 0x18);
    TextDrawAlign(gData_080BB110[gUnk_03000674 + 1].unk0C, TextGetAreaWidth() / 2, 0);
    TextSetCursor(0, 0x28);
    TextDrawAlign(gData_080BB110[gUnk_03000674 + 2].unk0C, TextGetAreaWidth() / 2, 0);

    if (gUnk_03000678 == 0)
    {
        TextRowSetPaletteBank(5, 0x0E, 3, 0x1A);
        TextRowSetPaletteBank(6, 0x0E, 3, 0x1A);
    }
    else if (gUnk_03000678 == 1)
    {
        TextRowSetPaletteBank(7, 0x0E, 3, 0x1A);
        TextRowSetPaletteBank(8, 0x0E, 3, 0x1A);
    }
    else if (gUnk_03000678 == 2)
    {
        TextRowSetPaletteBank(9, 0x0E, 3, 0x1A);
        TextRowSetPaletteBank(10, 0x0E, 3, 0x1A);
    }
}
