#include "global.h"

/* Choose how many gauge bars the bit beast summon spends.
 *
 * In a battle the fighter handler (sub_08034BE0) summons the bit beast while
 * L and R are held. Its gauge reading is 0..36; dividing by 12 gives the bars
 * (1..3) and the summon animation uses that number. BitBeastBars replaces that
 * division. With two or more bars it stops the battle in a loop of its own
 * (nothing else runs, so the scene stays on screen as if paused), draws a big
 * copy of the gauge wheel with the damage the summon should deal above it, and
 * lets Left / Right pick how many bars to spend, A summon, B cancel. The retail
 * code then goes on with the number returned (0 = no summon).
 *
 * The picture is four 64x64 OBJ sprites. They go to the lowest OAM entries (so
 * they are drawn over the game's sprites, which shift up four entries and keep
 * their order), into OBJ tiles and an OBJ palette bank no visible sprite uses.
 * Every other colour of the screen is darkened, as the pause screen does, so
 * the picture stands out. All of it is put back afterwards. */

#define KEY_A 0x001
#define KEY_B 0x002
#define KEY_RIGHT 0x010
#define KEY_LEFT 0x020
#define KEY_MASK 0x3FF

#define MAX_BARS 3

/* Fighter record (BattleWork + 0x478 is player 0, the human; 0x318 apart). */
#define FIGHTER_INDEX 0x30C /* u8: 0 = human, 1 = opponent */
#define FIGHTER_KEYS 0x300 /* u16 x 3: held, input mask, newly pressed (BtlCaptureInput) */
#define FIGHTER_STATS 0x4 /* pointer to {.. +0xC rpm, +0x10 attack, +0x14 defense, +0x18 endurance} */
#define FIGHTER_SIZE 0x318
#define STATS_RPM 0xC
#define STATS_ATTACK 0x10
#define STATS_DEFENSE 0x14
#define STATS_ENDURANCE 0x18

/* Battle input words (asm/ram_map_iwram.s): the mask keeps bits 10..15 set. */
#define GBTL_INPUT_MASK 0x03003F60
#define GBTL_KEYS_HELD 0x03004060
#define GBTL_KEYS_NEW 0x0300406C

/* BattleWork: gauge (current) and capacity per fighter, 4 bytes each. */
#define BATTLE_GAUGE 0xBBC
#define BATTLE_GAUGE_CAP 0xBC4

/* While a summon runs, every hit of the beast takes attack + defense +
 * endurance of the summoner off the opponent's RPM (the clash resolver,
 * sub_0802FFAC, with the bit beast power of sub_080300D4). The number of hits is
 * what the three bar animations produce, measured in play: about 12, 23, 35. */
static const u8 sHits[MAX_BARS + 1] = { 0, 12, 23, 35 };

/* The picture: 128 x 128 pixels, 4 bits per pixel, as four 64x64 sprites in
 * reading order (top left, top right, bottom left, bottom right). */
#define PANEL_W 128
#define PANEL_H 128
#define SPRITES 4
#define SPRITE_TILES 64
#define SPRITE_BYTES (SPRITE_TILES * 32)
#define PANEL_BYTES (SPRITES * SPRITE_BYTES)
#define PANEL_X ((240 - PANEL_W) / 2)
#define PANEL_Y ((160 - PANEL_H) / 2)

/* Where things sit in the picture. */
#define TEXT_Y 2 /* damage, 2x text */
#define WHEEL_X 64
#define WHEEL_Y 54
#define WHEEL_R 32
#define COUNT_Y 92
#define HINT_Y 114

#define OAM_COUNT 128
#define OAM_ADDR 0x07000000
#define OBJ_VRAM_ADDR 0x06010000
#define OBJ_PAL_ADDR 0x05000200
#define OBJ_TILES 1024
#define PALETTE_RAM 0x05000000
#define PALETTE_COLORS 512 /* BG and OBJ */

/* Palette indices of the picture. The wheel's colours are the HUD gauge's:
 * blue and teal, green and yellow, red and orange. */
#define C_NONE 0
#define C_WHITE 1
#define C_BLACK 2
#define C_HINT 3
#define C_EMPTY 4
#define C_ARROW_DIM 5
#define C_BLUE 6
#define C_TEAL 7
#define C_GREEN 8
#define C_RED 9
#define C_ORANGE 10
#define C_YELLOW 11

#define RGB(r, g, b) ((r) | ((g) << 5) | ((b) << 10))

static const u16 sPalette[16] = {
    0,
    RGB(31, 31, 31),
    RGB(0, 0, 3),
    RGB(22, 24, 29),
    RGB(5, 5, 9),
    RGB(12, 12, 17),
    RGB(12, 18, 27), /* blue */
    RGB(16, 22, 24), /* teal */
    RGB(26, 28, 15), /* green */
    RGB(31, 5, 2), /* red */
    RGB(31, 14, 4), /* orange */
    RGB(31, 28, 8), /* yellow */
    0, 0, 0, 0,
};

/* 5 x 7 glyphs, one byte per row, bit 4 = leftmost pixel. */
struct Glyph {
    char ch;
    u8 rows[7];
};

static const struct Glyph sGlyphs[] = {
    { 'A', { 0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11 } },
    { 'B', { 0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E } },
    { 'C', { 0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E } },
    { 'E', { 0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F } },
    { 'G', { 0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0F } },
    { 'I', { 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E } },
    { 'K', { 0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11 } },
    { 'M', { 0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11 } },
    { 'O', { 0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E } },
    { 'P', { 0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10 } },
    { 'R', { 0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11 } },
    { 'S', { 0x0F, 0x10, 0x10, 0x0E, 0x01, 0x01, 0x1E } },
    { 'T', { 0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 } },
    { '0', { 0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E } },
    { '1', { 0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E } },
    { '2', { 0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F } },
    { '3', { 0x1E, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x1E } },
    { '4', { 0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02 } },
    { '5', { 0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E } },
    { '6', { 0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E } },
    { '7', { 0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08 } },
    { '8', { 0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E } },
    { '9', { 0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C } },
    { ':', { 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00 } },
    { '/', { 0x01, 0x02, 0x02, 0x04, 0x08, 0x08, 0x10 } },
    { 0, { 0 } },
};

/* State and buffers at gBars (ram.s). Nothing needs to survive between
 * activations except what BitBeastBars sets for BitBeastSummonStart. */
struct BarsState {
    u8 picture[PANEL_BYTES]; /* the picture being drawn, then copied to OBJ VRAM */
    u8 backup[PANEL_BYTES]; /* what the game had in the tiles the picture takes */
    u16 oam[OAM_COUNT * 4]; /* the game's OAM */
    u16 palette[PALETTE_COLORS]; /* the game's colours */
    u16 firstTile[SPRITES]; /* OBJ tile of each sprite's 64 tiles */
    s32 remain; /* gauge to put back once the summon has started */
    u8 pending; /* `remain` is waiting */
    u8 bank; /* OBJ palette bank of the picture */
};

extern struct BarsState gBars;

extern s32 _080740B0(s32 a, s32 b);
extern void _08034090(void *seq, void *fighter, void *other);
extern void sub_08060428(void);
extern void sub_08060438(void);
extern void sub_08060448(void);

/* ---- drawing into the picture ------------------------------------------ */

/* Pixel (x, y): sprite (y / 64) * 2 + x / 64, whose 64 tiles are in rows of 8
 * (1D OBJ mapping). */
static void Put(s32 x, s32 y, u32 color)
{
    u32 tile;
    u8 *p;

    if (x < 0 || y < 0 || x >= PANEL_W || y >= PANEL_H)
        return;
    tile = ((y >> 6) * 2 + (x >> 6)) * SPRITE_TILES + ((y & 63) >> 3) * 8 + ((x & 63) >> 3);
    p = &gBars.picture[tile * 32 + (y & 7) * 4 + ((x & 7) >> 1)];
    if (x & 1)
        *p = (*p & 0x0F) | (color << 4);
    else
        *p = (*p & 0xF0) | color;
}

static void Rect(s32 x, s32 y, s32 w, s32 h, u32 color)
{
    s32 i, j;

    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++)
            Put(x + i, y + j, color);
    }
}

static s32 Abs(s32 v)
{
    return v < 0 ? -v : v;
}

static const u8 *FindGlyph(char ch)
{
    const struct Glyph *g;

    for (g = sGlyphs; g->ch != 0; g++) {
        if (g->ch == ch)
            return g->rows;
    }
    return 0;
}

/* One glyph, `scale` times bigger; returns the advance. */
static s32 DrawChar(s32 x, s32 y, char ch, s32 scale, u32 color)
{
    const u8 *rows = FindGlyph(ch);
    s32 r, c;

    if (rows != 0) {
        for (r = 0; r < 7; r++) {
            for (c = 0; c < 5; c++) {
                if (rows[r] & (0x10 >> c))
                    Rect(x + c * scale, y + r * scale, scale, scale, color);
            }
        }
    }
    return 6 * scale;
}

static s32 TextWidth(const char *s, s32 scale)
{
    s32 n = 0;

    while (*s++ != 0)
        n++;
    return n * 6 * scale - scale;
}

static void DrawString(s32 x, s32 y, const char *s, s32 scale, u32 color)
{
    while (*s != 0)
        x += DrawChar(x, y, *s++, scale, color);
}

/* Text on a busy scene needs an outline: the string in black one pixel off in
 * every direction, then in colour. Centred on the picture. */
static void DrawCentered(s32 y, const char *s, s32 scale, u32 color)
{
    s32 x = (PANEL_W - TextWidth(s, scale)) / 2;
    s32 dx, dy;

    for (dy = -1; dy <= 1; dy++) {
        for (dx = -1; dx <= 1; dx++) {
            if (dx != 0 || dy != 0)
                DrawString(x + dx, y + dy, s, scale, C_BLACK);
        }
    }
    DrawString(x, y, s, scale, color);
}

/* Decimal digits of n into out; returns the end. */
static char *PutNumber(char *out, u32 n)
{
    char tmp[10];
    s32 len = 0;

    do {
        tmp[len++] = '0' + n % 10;
        n /= 10;
    } while (n != 0);
    while (len > 0)
        *out++ = tmp[--len];
    return out;
}

/* The wheel is cut into three 120 degree slices by spokes pointing down, up
 * left and up right. Each slice has two tones split along its middle:
 *   bar 1 lower left   blue (towards the spoke below) / teal
 *   bar 2 top          green (left) / yellow (right)
 *   bar 3 lower right  red (towards the spoke below) / orange
 * A slice that is chosen is lit, one that is available but not chosen is
 * dithered with the empty colour, the rest is empty. The tests use slopes of
 * 7/12 (tan 30 degrees) so no trigonometry is needed. */
static const u8 sSliceTones[3][2] = {
    { C_BLUE, C_TEAL },
    { C_GREEN, C_YELLOW },
    { C_RED, C_ORANGE },
};

static void WheelPixel(s32 x, s32 y, s32 spend, s32 bars)
{
    s32 r2 = x * x + y * y;
    s32 slice;
    s32 tone;
    u32 lit;

    if (r2 > WHEEL_R * WHEEL_R)
        return;
    if (r2 > (WHEEL_R - 1) * (WHEEL_R - 1)) {
        Put(WHEEL_X + x, WHEEL_Y + y, C_BLACK);
        return;
    }
    if (r2 > (WHEEL_R - 4) * (WHEEL_R - 4) || r2 <= 16
        || ((x == 0 || x == -1) && y > 0)
        || (x < 0 && y <= 0 && Abs(7 * x - 12 * y) <= 14)
        || (x > 0 && y <= 0 && Abs(7 * x + 12 * y) <= 14)) {
        Put(WHEEL_X + x, WHEEL_Y + y, C_WHITE); /* rim, hub, spokes */
        return;
    }
    if (x < 0 && 7 * x < 12 * y) {
        slice = 0;
        tone = 12 * y < -7 * x ? 1 : 0;
    } else if (x >= 0 && -7 * x < 12 * y) {
        slice = 2;
        tone = 12 * y < 7 * x ? 1 : 0;
    } else {
        slice = 1;
        tone = x >= 0 ? 1 : 0;
    }
    lit = sSliceTones[slice][tone];
    if (slice >= spend)
        lit = slice < bars ? (((x + y) & 1) ? lit : C_EMPTY) : C_EMPTY;
    Put(WHEEL_X + x, WHEEL_Y + y, lit);
}

static void DrawWheel(s32 spend, s32 bars)
{
    s32 x, y;

    for (y = -WHEEL_R; y <= WHEEL_R; y++) {
        for (x = -WHEEL_R; x <= WHEEL_R; x++)
            WheelPixel(x, y, spend, bars);
    }
}

/* Triangle 8 wide, 14 tall, pointing left or right. */
static void DrawArrow(s32 x, s32 y, bool32 right, u32 color)
{
    s32 c;

    for (c = 0; c < 8; c++) {
        s32 h = (c + 1) * 14 / 8;
        s32 col = right ? 7 - c : c;

        Rect(x + col, y + 7 - h / 2, 1, h, color);
    }
}

/* `damage` is the estimated RPM the summon takes off the opponent, `ko` when
 * that is all of it. */
static void DrawPicture(s32 spend, s32 bars, s32 damage, bool32 ko)
{
    char text[16];
    char *end;
    u32 *w = (u32 *)gBars.picture;
    u32 i;
    s32 x;

    for (i = 0; i < PANEL_BYTES / 4; i++)
        w[i] = 0; /* transparent */

    end = PutNumber(text, damage);
    *end++ = ' ';
    *end++ = 'R';
    *end++ = 'P';
    *end++ = 'M';
    *end = 0;
    DrawCentered(TEXT_Y, text, 2, ko ? C_RED : C_WHITE);

    DrawWheel(spend, bars);

    text[0] = '0' + spend;
    text[1] = '/';
    text[2] = '0' + bars;
    text[3] = 0;
    DrawCentered(COUNT_Y, text, 2, C_WHITE);
    x = (PANEL_W - TextWidth(text, 2)) / 2;
    DrawArrow(x - 20, COUNT_Y, FALSE, spend > 1 ? C_WHITE : C_ARROW_DIM);
    DrawArrow(x + TextWidth(text, 2) + 12, COUNT_Y, TRUE, spend < bars ? C_WHITE : C_ARROW_DIM);

    DrawCentered(HINT_Y, "A: GO   B: BACK", 1, C_HINT);
}

/* ---- hardware ---------------------------------------------------------- */

static void CopyWords(void *dst, const void *src, u32 bytes)
{
    u32 *d = dst;
    const u32 *s = src;
    u32 i;

    for (i = 0; i < bytes / 4; i++)
        d[i] = s[i];
}

static void CopyHalves(vu16 *dst, const u16 *src, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++)
        dst[i] = src[i];
}

static u16 *SpriteTiles(u32 k)
{
    return (u16 *)(OBJ_VRAM_ADDR + gBars.firstTile[k] * 32);
}

/* OBJ tiles a sprite covers (1D mapping) and whether it can be seen. */
static u32 SpriteTileCount(u32 attr0, u32 attr1)
{
    static const u8 counts[3][4] = {
        { 1, 4, 16, 64 }, /* square */
        { 2, 4, 8, 32 }, /* wide */
        { 2, 4, 8, 32 }, /* tall */
    };
    u32 shape = attr0 >> 14;
    u32 n;

    if (shape > 2)
        return 0;
    n = counts[shape][attr1 >> 14];
    return (attr0 & 0x2000) ? n * 2 : n; /* 256 colours: two 4bpp tiles each */
}

static bool32 SpriteHidden(u32 attr0)
{
    u32 y = attr0 & 0xFF;

    if ((attr0 & 0x300) == 0x200)
        return TRUE;
    return y >= 160 && y < 192; /* below the screen, no sprite is tall enough to wrap */
}

/* Look at what the game's visible sprites use and pick, for the picture, an
 * OBJ palette bank and four runs of 64 OBJ tiles nobody uses (so the game's
 * sprites keep their look while the picture is up). */
static void Plan(void)
{
    u8 used[OBJ_TILES];
    u32 banks = 0;
    u32 i, k, t, n, first;

    for (i = 0; i < OBJ_TILES; i++)
        used[i] = 0;
    for (i = 0; i < OAM_COUNT; i++) {
        u32 a0 = gBars.oam[i * 4];
        u32 a1 = gBars.oam[i * 4 + 1];
        u32 a2 = gBars.oam[i * 4 + 2];

        if (SpriteHidden(a0))
            continue;
        if (!(a0 & 0x2000))
            banks |= 1 << (a2 >> 12);
        t = a2 & 0x3FF;
        for (n = SpriteTileCount(a0, a1); n > 0 && t < OBJ_TILES; n--, t++)
            used[t] = 1;
    }
    gBars.bank = 15;
    for (i = 15; i > 0; i--) {
        if (!(banks & (1 << i))) {
            gBars.bank = i;
            break;
        }
    }

    /* Bitmap modes (3 to 5) only draw OBJ tiles from 512 up. */
    first = (REG_DISPCNT & 7) >= 3 ? 512 : 0;
    for (k = 0; k < SPRITES; k++) {
        gBars.firstTile[k] = OBJ_TILES - SPRITE_TILES * (k + 1); /* fallback: the last tiles */
        for (t = OBJ_TILES - SPRITE_TILES; t >= first && t < OBJ_TILES; t--) {
            bool32 free = TRUE;

            for (i = 0; i < SPRITE_TILES; i++) {
                if (used[t + i])
                    free = FALSE;
            }
            if (free) {
                gBars.firstTile[k] = t;
                for (i = 0; i < SPRITE_TILES; i++)
                    used[t + i] = 1;
                break;
            }
        }
    }
}

static void ShowPicture(void)
{
    vu16 *oam = (vu16 *)OAM_ADDR;
    u32 k;

    VBlankIntrWait();
    for (k = 0; k < SPRITES; k++)
        CopyWords(SpriteTiles(k), gBars.picture + k * SPRITE_BYTES, SPRITE_BYTES);
    for (k = 0; k < SPRITES; k++) {
        oam[k * 4 + 0] = PANEL_Y + (k >> 1) * 64; /* square, normal, 16 colours */
        oam[k * 4 + 1] = (PANEL_X + (k & 1) * 64) | 0xC000; /* 64 pixels */
        oam[k * 4 + 2] = gBars.firstTile[k] | (gBars.bank << 12); /* priority 0: in front */
    }
}

/* Every colour of the screen at about half brightness (not the picture's bank). */
static u16 Dim(u16 c)
{
    return (((c & 31) * 9) >> 4) | (((((c >> 5) & 31) * 9) >> 4) << 5) | (((((c >> 10) & 31) * 9) >> 4) << 10);
}

static void Open(void)
{
    vu16 *oam = (vu16 *)OAM_ADDR;
    vu16 *pal = (vu16 *)PALETTE_RAM;
    u32 i, k;

    for (i = 0; i < OAM_COUNT * 4; i++)
        gBars.oam[i] = oam[i];
    for (i = 0; i < PALETTE_COLORS; i++)
        gBars.palette[i] = pal[i];
    Plan();
    for (k = 0; k < SPRITES; k++)
        CopyWords(gBars.backup + k * SPRITE_BYTES, SpriteTiles(k), SPRITE_BYTES);

    VBlankIntrWait();
    /* The game's sprites move up four entries, attributes 0..2 only (3 belongs
     * to the affine parameters), which keeps their order; the last four are
     * hidden ones unless the game uses every entry, then they are lost. */
    for (i = OAM_COUNT - 1; i >= SPRITES; i--) {
        oam[i * 4] = gBars.oam[(i - SPRITES) * 4];
        oam[i * 4 + 1] = gBars.oam[(i - SPRITES) * 4 + 1];
        oam[i * 4 + 2] = gBars.oam[(i - SPRITES) * 4 + 2];
    }
    for (i = 0; i < PALETTE_COLORS; i++)
        pal[i] = Dim(gBars.palette[i]);
    pal = (vu16 *)(OBJ_PAL_ADDR + gBars.bank * 32);
    for (i = 0; i < 16; i++)
        pal[i] = sPalette[i];
}

static void Close(void)
{
    vu16 *oam = (vu16 *)OAM_ADDR;
    u32 k;

    VBlankIntrWait();
    for (k = 0; k < SPRITES; k++)
        CopyWords(SpriteTiles(k), gBars.backup + k * SPRITE_BYTES, SPRITE_BYTES);
    CopyHalves((vu16 *)PALETTE_RAM, gBars.palette, PALETTE_COLORS);
    CopyHalves(oam, gBars.oam, OAM_COUNT * 4);
}

static u32 Keys(void)
{
    return ~REG_KEYINPUT & KEY_MASK;
}

/* The popup. Returns the bars chosen, 0 for cancel. `power` is the damage of
 * one hit of the beast, `opponentRpm` what the opponent has left. */
static s32 Choose(s32 bars, s32 power, s32 opponentRpm)
{
    s32 spend = bars;
    u32 held = Keys();
    u32 pressed;
    s32 quiet = 0;
    s32 damage = power * sHits[spend];

    Open();
    DrawPicture(spend, bars, damage, damage >= opponentRpm);
    ShowPicture();
    sub_08060428();

    for (;;) {
        s32 want = spend;
        bool32 cancel = FALSE;
        bool32 confirm = FALSE;

        VBlankIntrWait();
        pressed = Keys() & ~held;
        held = Keys();
        if (pressed & KEY_RIGHT)
            want = spend + 1;
        if (pressed & KEY_LEFT)
            want = spend - 1;
        if (pressed & KEY_A)
            confirm = TRUE;
        if (pressed & KEY_B)
            cancel = TRUE;
        if (want >= 1 && want <= bars && want != spend) {
            spend = want;
            damage = power * sHits[spend];
            DrawPicture(spend, bars, damage, damage >= opponentRpm);
            ShowPicture();
            sub_08060448();
        }
        if (confirm || cancel) {
            if (cancel) {
                spend = 0;
                sub_08060438();
            }
            break;
        }
    }

    /* Let go of every key before the game sees them again, or the A that
     * confirmed would also be read as an attack. */
    while (quiet < 3) {
        VBlankIntrWait();
        quiet = Keys() == 0 ? quiet + 1 : 0;
    }
    Close();
    return spend;
}

/* ---- hooks ------------------------------------------------------------- */

/* Replaces `bl _080740B0` (gauge reading, 12) in the summon code; `fighter`
 * is the fighter record the handler runs for (r4, see thunk.s). */
s32 BitBeastBars(s32 gauge, s32 per, u8 *fighter)
{
    s32 bars = _080740B0(gauge, per);
    s32 spend;
    s32 power;
    u8 *battle;
    u8 *own;
    u8 *other;
    s32 cap;

    gBars.pending = FALSE;
    if (fighter[FIGHTER_INDEX] != 0 || bars < 2)
        return bars;
    if (bars > MAX_BARS)
        bars = MAX_BARS;

    own = *(u8 **)(fighter + FIGHTER_STATS);
    other = *(u8 **)(fighter + FIGHTER_SIZE + FIGHTER_STATS);
    power = *(s32 *)(own + STATS_ATTACK) + *(s32 *)(own + STATS_DEFENSE) + *(s32 *)(own + STATS_ENDURANCE);
    spend = Choose(bars, power, *(s32 *)(other + STATS_RPM));
    /* The game's key words still hold the L+R from before the popup (its input
     * routine did not run meanwhile), and the fighter a copy of them; it would
     * summon again next frame. Every key is up now, so say so. */
    *(vu16 *)GBTL_INPUT_MASK &= 0xFC00;
    *(vu16 *)GBTL_KEYS_HELD = 0;
    *(vu16 *)GBTL_KEYS_NEW = 0;
    *(u16 *)(fighter + FIGHTER_KEYS) = 0;
    *(u16 *)(fighter + FIGHTER_KEYS + 2) = 0;
    *(u16 *)(fighter + FIGHTER_KEYS + 4) = 0;
    if (spend > 0 && spend < bars) {
        /* Retail zeroes the gauge when the summon starts; keep what was not
         * spent. One bar is a third of the capacity. */
        battle = (u8 *)gBattleWork;
        cap = *(s32 *)(battle + BATTLE_GAUGE_CAP);
        gBars.remain = *(s32 *)(battle + BATTLE_GAUGE) - spend * (cap / MAX_BARS);
        if (gBars.remain < 0)
            gBars.remain = 0;
        gBars.pending = TRUE;
    }
    return spend;
}

/* Replaces `bl _08034090` (start of the summon sequence). */
void BitBeastSummonStart(void *seq, void *fighter, void *other)
{
    _08034090(seq, fighter, other);
    if (gBars.pending) {
        *(s32 *)((u8 *)gBattleWork + BATTLE_GAUGE) = gBars.remain;
        gBars.pending = FALSE;
    }
}
