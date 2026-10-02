#include "debug_menu.h"

/* The overworld's own popup-menu machinery (the Start menu is "page 7") runs
 * a page definition: init / loop / exit functions plus one handler per key,
 * driven by MainCallbacksRun and MenuDispatchKeyHandlers. This file supplies a
 * page of that shape and opens it with L. Drawing mirrors the Start menu: a
 * frame font for the border pieces, the text font for labels, and palette
 * banks 0x0F / 0x0E for normal / highlighted rows. */

#define KEY_A 0x001
#define KEY_B 0x002
#define KEY_START 0x008
#define KEY_L 0x200

#define FRAME_FONT ((struct Unk617C4 *)0x080D79CC)
#define FRAME_WIDTHS 0x080B7429
#define TEXT_FONT ((struct Unk617C4 *)0x082BCD00)
#define TEXT_WIDTHS 0x080B738E

/* Border strings, as the Start menu uses them but wider: first/last glyph are
 * the corners (A/C top, G/I sides, D/F bottom), the rest the edge fill. */
#define FRAME_GLYPHS 24 /* frame width in 8px glyphs */
static const char sFrameTop[] = "ABBBBBBBBBBBBBBBBBBBBBBC";
static const char sFrameMid[] = "GHHHHHHHHHHHHHHHHHHHHHHI";
static const char sFrameBottom[] = "DEEEEEEEEEEEEEEEEEEEEEEF";
#define FRAME_TOP ((void *)sFrameTop)
#define FRAME_MID ((void *)sFrameMid)
#define FRAME_BOTTOM ((void *)sFrameBottom)

#define VISIBLE_ROWS 6
#define WINDOW_COLS 28
#define MENU_MODE_LOOP 1
#define MENU_MODE_EXIT 2
#define MENU_MODE_DONE 3

extern void sub_08060428(void);
extern void sub_08060438(void);
extern void sub_08060448(void);

struct MenuPage {
    void (*init)(u8 *state, struct MainWork *work);
    void (*loop)(u8 *state, struct MainWork *work);
    void (*exit)(u8 *state, struct MainWork *work);
    void *frame;
    void *unk10;
    void *unk14;
    void (*onLeft)(u8 *state);
    void (*onRight)(u8 *state);
    void (*onUp)(u8 *state);
    void (*onDown)(u8 *state);
    void (*onA)(u8 *state);
    void (*onB)(u8 *state);
    u8 pad[0x18];
    u16 fadeA;
    u16 fadeB;
    u16 fadeC;
    u8 keyMode;
    u8 pad2;
};

static const char *const sLabels[DBG_ITEM_COUNT] = {
    "Max RPM",
    "Max STR",
    "Max EXP",
    "Max Level",
    "Max Credits",
    "All BeyBlades",
    "All Parts",
    "All Characters",
    "All Locations",
    "Max BitBeast EXP",
    "Inf. BeyBlade Health",
    "Infinite Ripcord",
    "Infinite Launcher",
    "Movement Speed",
    "BGM",
    "Character",
};

void DebugStateInit(void)
{
    u8 *p;
    u32 i;

    if (gDebug.magic == DBG_MAGIC)
        return;
    p = (u8 *)&gDebug;
    for (i = 0; i < sizeof(gDebug); i++)
        p[i] = 0;
    gDebug.magic = DBG_MAGIC;
    gDebug.value[DBG_MOVE_SPEED] = 1;
}

static u8 *PutNumber(u8 *out, u32 n)
{
    u8 tmp[10];
    s32 len = 0;

    do {
        tmp[len++] = '0' + n % 10;
        n /= 10;
    } while (n != 0);
    while (len > 0)
        *out++ = tmp[--len];
    return out;
}

/* Entries still waiting for the game data they need (see README). They show
 * "n/a" and do nothing. */
static bool32 IsAvailable(u32 item)
{
    return item != DBG_ALL_LOCATIONS && item != DBG_CHARACTER;
}

static void ValueText(u32 item, u8 *out)
{
    u8 v = gDebug.value[item];
    u8 *p = out;

    if (!IsAvailable(item)) {
        *p++ = 'n';
        *p++ = '/';
        *p++ = 'a';
        *p = 0;
        return;
    }
    switch (item) {
    case DBG_MOVE_SPEED:
        *p++ = 'x';
        p = PutNumber(p, v);
        break;
    case DBG_BGM:
    case DBG_CHARACTER:
        p = PutNumber(p, v);
        break;
    default:
        if (v) {
            *p++ = 'O';
            *p++ = 'N';
        } else {
            *p++ = 'O';
            *p++ = 'F';
            *p++ = 'F';
        }
        break;
    }
    *p = 0;
}

/* Frame geometry in BG map columns: the window starts at column 1 and the
 * frame is centred in it. */
static u32 FrameBorderCol(void)
{
    return 1 + (WINDOW_COLS - FRAME_GLYPHS) / 2;
}

static void DrawFrameTop(void)
{
    TextSetActiveObject(FRAME_FONT, FRAME_WIDTHS);
    TextSetCursor(0, 0);
    TextSetPaletteBank(0x0F);
    TextDrawAlign(FRAME_TOP, TextGetAreaWidth() >> 1, 0);
}

static void DrawRow(u32 row, u32 item)
{
    u8 value[8];
    const char *text;
    u32 y = row << 4;
    u32 half = TextGetAreaWidth() >> 1;
    u32 left = half - FRAME_GLYPHS * 4 + 10;
    u32 right = half + FRAME_GLYPHS * 4 - 10;

    TextSetActiveObject(FRAME_FONT, FRAME_WIDTHS);
    TextSetCursor(0, y + 8);
    TextDrawAlign(FRAME_MID, half, 0);
    TextSetCursor(0, y + 0x10);
    TextDrawAlign(FRAME_MID, half, 0);
    TextSetActiveObject(TEXT_FONT, TEXT_WIDTHS);
    TextSetCursor(0, y + 8);
    TextDrawAlign((void *)sLabels[item], left, 2);
    ValueText(item, value);
    text = item == DBG_BGM ? BgmName(gDebug.value[DBG_BGM]) : (const char *)value;
    TextSetCursor(0, y + 8);
    TextDrawAlign((void *)text, right, 1);
}

static void DrawFrameBottom(void)
{
    TextSetActiveObject(FRAME_FONT, FRAME_WIDTHS);
    TextSetCursor(0, 8 + VISIBLE_ROWS * 16);
    TextSetPaletteBank(0x0F);
    TextDrawAlign(FRAME_BOTTOM, TextGetAreaWidth() >> 1, 0);
}

static void Highlight(void)
{
    u32 border = FrameBorderCol();
    u32 first = border + 1;
    u32 last = border + FRAME_GLYPHS - 2;
    u32 row;

    for (row = 0; row < VISIBLE_ROWS * 2; row++)
        TextRowSetPaletteBank(5 + row, 0x0F, first, last);
    row = (gDebug.cursor - gDebug.top) * 2;
    TextRowSetPaletteBank(5 + row, 0x0E, first, last);
    TextRowSetPaletteBank(6 + row, 0x0E, first, last);
}

static void DrawAll(void)
{
    s32 i;

    TextWindowClearActiveTiles();
    DrawFrameTop();
    VBlankIntrWait();
    for (i = 0; i < VISIBLE_ROWS; i++)
        DrawRow(i, gDebug.top + i);
    DrawFrameBottom();
    Highlight();
}

static void SetFade(struct MainWork *work)
{
    REG_BLDCNT = 0x3748;
    REG_BLDALPHA = (work->unk17F2 << 8) | work->unk17F0;
}

static void MenuInit(u8 *state, struct MainWork *work)
{
    state[0x2D4] = MENU_MODE_LOOP;
    work->unk17F0 = 0;
    work->unk17F2 = 0x10;
    SetFade(work);
    DrawAll();
    work->unk1808 |= 0x40;
}

static void BeginClose(u8 *state)
{
    struct MainWork *work = gMainWorkPtr;

    sub_08060438();
    state[0x2D4] = MENU_MODE_EXIT;
    work->unk17F0 = 0x10;
    work->unk17F2 = 0;
}

static void MenuLoop(u8 *state, struct MainWork *work)
{
    if (work->unk17F2 != 0) {
        work->unk17F2--;
        work->unk17F0++;
    }
    SetFade(work);
    if (gData_03004060 & (KEY_START | KEY_L))
        BeginClose(state);
}

static void MenuExit(u8 *state, struct MainWork *work)
{
    if (work->unk17F0 != 0) {
        work->unk17F0--;
        work->unk17F2++;
        SetFade(work);
        return;
    }
    work->unk1808 &= ~0x40;
    TextWindowClearActiveTiles();
    state[0x2D4] = MENU_MODE_DONE;
    work->unk184D = 0;
    REG_BLDCNT = 0;
    REG_BLDALPHA = 0;
}

static void Scroll(void)
{
    if (gDebug.cursor < gDebug.top)
        gDebug.top = gDebug.cursor;
    else if (gDebug.cursor >= gDebug.top + VISIBLE_ROWS)
        gDebug.top = gDebug.cursor - VISIBLE_ROWS + 1;
}

static void OnUp(u8 *state)
{
    u8 top = gDebug.top;

    gDebug.cursor = gDebug.cursor == 0 ? DBG_ITEM_COUNT - 1 : gDebug.cursor - 1;
    Scroll();
    if (top != gDebug.top)
        DrawAll();
    else
        Highlight();
    sub_08060448();
}

static void OnDown(u8 *state)
{
    u8 top = gDebug.top;

    gDebug.cursor = gDebug.cursor == DBG_ITEM_COUNT - 1 ? 0 : gDebug.cursor + 1;
    Scroll();
    if (top != gDebug.top)
        DrawAll();
    else
        Highlight();
    sub_08060448();
}

static void Redraw(void)
{
    DrawAll();
}

/* Entries that hold a setting rather than an on/off state. */
static bool32 IsSetting(u32 item)
{
    return item == DBG_MOVE_SPEED || item == DBG_BGM;
}

static void Step(s32 delta)
{
    u32 item = gDebug.cursor;
    s32 v = gDebug.value[item];
    s32 lo = 0;
    s32 hi;

    if (!IsAvailable(item))
        return;

    switch (item) {
    case DBG_MOVE_SPEED:
        lo = 1;
        hi = MAX_MOVE_SPEED;
        break;
    case DBG_BGM:
        hi = BGM_TRACKS - 1;
        break;
    default:
        hi = 1;
        break;
    }
    v += delta;
    if (v > hi)
        v = lo;
    else if (v < lo)
        v = hi;
    gDebug.value[item] = v;
    if (IsSetting(item))
        CheatsOnChange(item);
    else
        CheatsOnToggle(item);
    Redraw();
    sub_08060448();
}

static void OnA(u8 *state)
{
    Step(1);
}

static void OnLeft(u8 *state)
{
    if (IsSetting(gDebug.cursor))
        Step(-1);
}

static void OnRight(u8 *state)
{
    if (IsSetting(gDebug.cursor))
        Step(1);
}

static void OnB(u8 *state)
{
    BeginClose(state);
}

static const struct MenuPage sDebugPage = {
    MenuInit, MenuLoop, MenuExit, 0, 0, 0,
    OnLeft, OnRight, OnUp, OnDown, OnA, OnB,
    {0}, 0, 0, 0, 0, 0,
};

static void OpenMenu(void)
{
    struct MainWork *work = gMainWorkPtr;

    /* Show the track that is actually playing. */
    if (work->bgmTrack >= 0 && work->bgmTrack < BGM_TRACKS)
        gDebug.value[DBG_BGM] = work->bgmTrack;

    sub_0804109C((struct MenuState *)&work->unk0530, (struct Unk4109CInput *)&sDebugPage);
    work->unk181C = 3;
    sub_08060428();
}

/* Called in place of HudRefreshStats at the end of the overworld frame. */
void DebugFieldTick(void)
{
    struct MainWork *work;

    HudRefreshStats();
    DebugStateInit();
    CheatsTick();
    work = gMainWorkPtr;
    if ((gData_03004060 & KEY_L) && work->unk180C == 0 && work->unk185A == 1)
        OpenMenu();
}
