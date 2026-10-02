#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_08031300 */
// @ 0x08031300
void TextRowPulsePalette(struct Unk312EC *a)
{
    struct Sprite *p;
    u32 bank;

    if (a->unk08 == 0)
        return;
    if (a->unk04 >= 0)
    {
        a->unk04--;
        p = a->unk0C;
        if (p == NULL)
            return;
        bank = p->unk14 >> 12;
        if ((a->unk04 & 5) == 0)
        {
            if (bank == a->unk01)
                bank = a->unk00;
            else
                bank = a->unk01;
            TextEntrySetPaletteBank(p, (u8)bank);
        }
    }
    else
    {
        PaletteHighlightEnd(a);
    }
}

/* fn: sub_0803D284 */
// @ 0x0803d284
/* match-compiler: old_agbcc */
// Lay out `str` as a centred row of glyph sprites in BattleWork.unk0BCC:
// hide all 48 entries, then give each non-space character its own entry
// (spaces just advance x by 4). Glyphs map through gData_080BB748 and
// advance by 0x10 minus that glyph's entry in `widths`.
void BattleTextGlyphRow(const u8 *str, s32 b, const u8 *widths, s32 y)
{
    s32 i;
    s32 x;
    s32 n;

    for (i = 0; i <= 0x2F; i++)
    {
        gBattleWork->unk0BCC[i].posX = -0x4000;
        gBattleWork->unk0BCC[i].posY = -0x4000;
        sub_08062238(&gBattleWork->unk0BCC[i]);
    }
    x = 0x76 - (TextMeasureWidth(str, widths, 0x10, 4) >> 1);
    for (n = 0, i = 0; str[i] != 0; i++)
    {
        if (str[i] != ' ')
        {
            sub_0806211C(&gBattleWork->unk0BCC[n], NULL, (struct Unk6FF58Src *)b, x, y, 0, 0x28, 0, gData_080BB748[str[i]]);
            x += 0x10 - widths[gData_080BB748[str[i]]];
            sub_08062634(&gBattleWork->unk0BCC[n], -1, n * 2, 0x0803D27D);
            TextEntrySetPaletteBank(gBattleWork->unk0BCC[n].sprite, 0);
            BtlObjListResort((struct Unk6FDB4 *)gBattleWork->unk0BCC[n].sprite, 40000 - n);
            n++;
        }
        else
            x += 4;
    }
}

/* fn: sub_080610A8 */
// @ 0x080610a8

void TextSetCursorAligned(
    struct Unk610A8 *base,
    u8 *text,
    u32 index,
    u32 mode)
{
    s32 value;

    if (base == 0 || index >= base->unk98)
        return;
    value = TextMeasureWidth(text, base->unk8C, base->unkA0, base->unk9C);
    switch (mode)
    {
    case 0:
        base->unk90 = index - ((u32)value >> 1);
        break;
    case 2:
        base->unk90 = index;
        break;
    case 1:
        base->unk90 = index - value;
        break;
    }
    TextWindowPutString(base, text);
}

/* fn: sub_08061564 */
// @ 0x08061564
/* match-compiler: old_agbcc */
// Run a text control stream: 7 = set cursor (x, y), 8 = palette bank,
// 10 = new line (wrapping the row) then set cursor; anything else is logged.
void TextDraw(u8 *data)
{
    u8 op;
    u8 x;
    u8 *cur;
    struct TextWindow *work;

    if (data == NULL || (op = *data) == 0)
        return;
    cur = data + 1;
    do
    {
        switch (op)
        {
        case 10:
            work = gUnk_03000798;
            work->penX = 0;
            work->penY = work->penY + work->lineHeight;
            if ((s16)work->penY > (work->height >> 3) - 1)
                work->penY = 0;
        case 7:
            x = *cur++;
            TextSetCursor(x, *cur++);
            break;
        case 8:
            TextSetPaletteBank(*cur++);
            break;
        default:
            _08073C44((void *)(u32)op, (void *)gData_080BB644[0]);
            break;
        }
    } while ((op = *cur++) != 0);

}

/* fn: sub_080615EC */
// @ 0x080615ec
/* match-flags: -fprologue-bugfix */

void TextSetCursor(u32 x, u32 y)
{
    u32 r2;
    u32 r3;
    struct TextWindow *r0;
    u16 *r1;

    r2 = x;
    r3 = y;
    if (r2 > 0xEF)
        r2 = 0;
    if (r3 > 0x9F)
        r3 = 0;
    r0 = gUnk_03000798;
    r1 = &r0->penX;
    *r1 = r2;
    r0->penY = r3;
}

/* fn: sub_08061610 */
// @ 0x08061610
void TextSetPaletteBank(u16 a)
{
    s32 v;
    struct TextWindow *p;

    v = a;
    p = gUnk_03000798;
    v &= 15;
    v <<= 12;
    p->baseTile = v;
}

/* fn: sub_0806171C */
// @ 0x0806171c

void TextDrawAlign(void *data, u32 index, u32 mode)
{
    s32 value;

    if (index >= gUnk_03000798->width)
        return;
    value = TextMeasureWidth(
        data,
        (void *)gUnk_03000798->widthTable,
        gUnk_03000798->glyphWidth,
        gUnk_03000798->spacing);
    switch (mode)
    {
    case 0:
        gUnk_03000798->penX = index - ((u32)value >> 1);
        break;
    case 2:
        gUnk_03000798->penX = index;
        break;
    case 1:
        gUnk_03000798->penX = index - value;
        break;
    }
    TextDraw(data);
}

/* fn: sub_08061784 */
// @ 0x08061784

u16 TextGetAreaWidth(void)
{
    return gUnk_03000798->width;
}

/* fn: sub_080617B4 */
// @ 0x080617b4

u16 TextGetSpacing(void)
{
    return gUnk_03000798->spacing;
}

/* fn: sub_080617C4 */
// @ 0x080617c4
/* match-compiler: old_agbcc */
// Register the object at gUnk_03000798 with the engine: store `a` and `b` in the two
// slots at +0x88/+0x8C, publish `a`'s two bytes at +0xA0/+0xA2, then derive the word at
// +0x9C from the halfword just written at +0xA0 (read back, not the local, which is why
// it survives as a reload). The `& 1` test on a->unk0C comes first and returns early.
// The table is a real typed lvalue (gUnk_03000798) so agbcc keeps the literal in one
// register instead of re-materialising it.
void TextSetActiveObject(struct Unk617C4 *a, u32 b)
{
    struct TextWindow *s;

    if ((a->unk0C & 1) == 0)
        return;
    s = gUnk_03000798;
    s->unk88 = a;
    s->widthTable = b;
    s->glyphWidth = a->unk04;
    s->lineHeight = a->unk05;
    s->spacing = s->glyphWidth >> 2;
}

/* fn: sub_080618A8 */
// @ 0x080618a8

void TextTypewriterInit(struct Unk618A8 *a, void *b, u16 c, u16 d, u16 e, u16 f)
{
    if (a == 0)
        return;
    if (b == 0)
        return;
    a->unk00 = b;
    a->unk08 = c;
    a->unk10 = 0;
    a->unk12 = d;
    a->unk0C = e;
    a->unk0E = f;
    a->unk0A = 0;
    a->unk15 = 0;
    a->unk04 = 0;
    a->unk14 = 1;
}

/* fn: sub_080618EC */
// @ 0x080618ec
/* match-compiler: old_agbcc */
// Typewriter text tick: counts down the per-character delay (quartered while
// fastKeys are held), starts and measures a new line, and prints one glyph or
// control code (7 = cursor, 8 = palette).

// `state` is a signed local on purpose: it keeps one multi-bit pseudo live to the
// `|= 0xFF` below, so the load goes straight into r3 and the OR is not folded.
s32 TextTypewriterTick(struct TextTypewriter *t, s32 x, u32 align, u32 stopLine)
{
    u8 *str;
    s8 state;
    u8 c;
    s32 width;

    if (t == NULL)
        return -1;
    if ((state = t->state) != 1)
        return (s8)t->state;
    if (gData_03003F60 & t->skipKeys)
    {
        t->state = 0xFF;
        return -1;
    }
    if (t->timer > 0)
    {
        t->timer--;
        return 1;
    }
    if (gData_03003F60 & t->fastKeys)
        t->timer = (s16)t->delay >> 2;
    else
        t->timer = t->delay;
    if (t->pos == 0 && t->len == 0)
    {
        if (t->line >= t->lineCount)
        {
            t->state |= 0xFF;
            return -1;
        }
        t->len = StringLength(t->lines[t->line]);
        if (t->len == 0)
        {
            t->state = 0xFF;
            return -1;
        }
        width = TextMeasureWidth(t->lines[t->line], (const u8 *)gData_03000798->widthTable, gData_03000798->glyphWidth, gData_03000798->spacing);
        switch (align)
        {
        case 0:
            gData_03000798->penX = x - ((u32)width >> 1);
            break;
        case 2:
            gData_03000798->penX = x;
            break;
        case 1:
            gData_03000798->penX = x - width;
            break;
        }
        gData_03000798->penY += gData_03000798->lineHeight;
        if (stopLine == t->line && t->len != 0)
        {
            gData_03000798->penY -= gData_03000798->lineHeight;
            return 2;
        }
    }
    str = t->lines[t->line];
    c = str[t->pos++];
    switch (c)
    {
    case 10:
        break;
    case 7:
        TextSetCursor(str[t->pos++] - 1, str[t->pos++] - 1);
        break;
    case 8:
        TextSetPaletteBank(str[t->pos++] - 1);
        break;
    default:
        if (t->pos > t->len)
        {
            t->pos = 0;
            t->len = 0;
            t->line++;
        }
        else
        {
            ((void (*)(u32))gData_080BB644[0])(c);
        }
        break;
    }
    return 1;
}

/* fn: sub_08061A98 */
// @ 0x08061a98

u32 TextGetWidthTable(void)
{
    return gUnk_03000798->widthTable;
}

/* fn: sub_08061AA8 */
// @ 0x08061aa8

u16 TextGetGlyphWidth(void)
{
    return gUnk_03000798->glyphWidth;
}

/* fn: sub_08061BDC */
// @ 0x08061bdc
/* match-flags: -fprologue-bugfix */

void TextTypewriterResume(struct Unk61BDC *a)
{
    struct Unk61BDC *r1;
    u32 r0;

    r1 = a;
    if (r1 != 0)
    {
        r0 = 1;
        r1->unk14 = r0;
    }
}

/* fn: sub_08061D68 */
// @ 0x08061d68
/* match-compiler: old_agbcc */

void TextRowSetPaletteBank(u32 a, u32 b, u32 c, u32 d)
{
    u16 palBits;
    u32 saved;
    u16 *addr;
    u16 mask;
    u32 base;
    u32 scaled;

    palBits = (u16)((b << 28) >> 16);
    a &= 0x1F;
    c &= 0x1F;
    saved = c;
    d &= 0x1F;
    if (d < c)
    {
        c = d;
        d = saved;
    }
    addr = (u16 *)(gUnk_03000798->screenBlock << 11);
    base = 0xC0;
    base <<= 19;
    addr = (u16 *)((u32)addr + base);
    addr = (u16 *)((u32)addr + (a << 6));
    if ((s32)c <= (s32)d)
    {
        mask = 0x3FF;
        scaled = (c << 1) + (u32)addr;
        addr = (u16 *)scaled;
        do
        {
            *addr = (*addr & mask) | palBits;
            addr++;
            c++;
        } while ((s32)c <= (s32)d);
    }
}

/* fn: sub_08061E40 */
// @ 0x08061e40

/* match-flags: -fprologue-bugfix */

void TextTypewriterRestart(struct Unk61E40 *a)
{
    if (a != 0)
    {
        a->unk10 = 0;
        a->unk0A = 0;
        a->unk15 = 0;
        a->unk04 = 0;
    }
}

/* fn: sub_08061E8C */
// @ 0x08061e8c
void GlyphTextInit(struct Unk61E8C *obj, void *b, struct Unk61E8CSrc *src, u16 c, u16 d)
{
    u32 *sym = gData_080BB8BC;
    u32 size;
    struct Unk61E8CAlloc *alloc;
    void *inner;

    _08073C4C(0, obj, 0x28, (void *)*sym);
    obj->unk04 = b;
    obj->unk08 = src;
    obj->unk20 = src->unk04;
    obj->unk22 = src->unk05;
    obj->unk1C = c;
    obj->unk1E = d;
    size = 0x80;
    size <<= 2;
    alloc = HeapAlloc(size);
    obj->unk00 = alloc;
    if (alloc != 0) {
        inner = alloc->unk00;
        obj->unk0C = inner;
        _08073C4C(0, inner, size, (void *)*sym);
    }
}

/* fn: sub_08061EF8 */
// @ 0x08061ef8
/* match-compiler: old_agbcc */
// Lays `text` out as glyph sprites: wraps it into up to four lines, aligns
// each line with sub_08062068 (`align`) and places one sprite per glyph,
// advancing by 0x10 minus the glyph's entry in the width table.
void GlyphTextLayoutWrapped(struct GlyphText *a, const u8 *text, u32 unused, s32 y, u32 paletteArg, u32 tileArg, u32 align)
{
    u8 *lines[4];
    u8 palette = paletteArg;
    u16 tile = tileArg;
    s32 count;
    s32 i;
    u8 *p;
    s32 x;
    u32 c;

    GlyphTextReleaseSprites(a);
    if (StringArrayAlloc((void **)lines, 4, 0x60) < 4)
    {
        StringArrayFree((void **)lines, 4);
        return;
    }
    count = SplitStringIntoStringArray((void **)lines, (u8 *)text, 4, (u32)a->widthTable, a->unk1C, a->glyphSize, a->glyphSize >> 2, 0x60);
    for (i = 0; i < count; i++)
    {
        p = lines[i];
        a->lastLineWidth = TextMeasureWidth(p, a->widthTable, a->glyphSize, a->glyphSize >> 2);
        x = sub_08062068((struct Unk62068 *)a, a->lastLineWidth, align);
        if (i == 0)
        {
            a->unk10 = x << 8;
            a->unk14 = y << 8;
        }
        for (c = *p++; c != 0; c = *p++)
        {
            if (c == ' ')
            {
                x += a->glyphSize >> 2;
            }
            else
            {
                a->sprites[a->spritesInUse] = BtlObjPoolAlloc(tile);
                if (a->sprites[a->spritesInUse] == NULL)
                    return;
                SpriteInitFromTemplate((struct Sprite *)a->sprites[a->spritesInUse], a->glyphSprite, x << 8, y << 8, 0, 0, 0, gData_080BB748[c]);
                x = 0x10 - a->widthTable[gData_080BB748[c]] + x;
                TextEntrySetPaletteBank((struct Sprite *)a->sprites[a->spritesInUse], palette);
                a->spritesInUse++;
            }
        }
        y += a->lineHeight;
    }
    StringArrayFree((void **)lines, 4);
}

/* fn: sub_08062044 */
// @ 0x08062044
void GlyphTextFree(struct GlyphText *a)
{
    if (a != 0)
    {
        GlyphTextReleaseSprites(a);
        if (a->heapBlock != 0)
        {
            HeapFree(a->heapBlock);
            a->heapBlock = 0;
        }
        a->sprites = 0;
    }
}

/* fn: sub_0806209C */
// @ 0x0806209c

void GlyphTextReleaseSprites(struct GlyphText *a)
{
    s32 i;
    void *p;

    if (a == 0)
        return;
    if (a->sprites != 0)
    {
        i = 0;
        do
        {
            p = a->sprites[i];
            if (p == 0)
                break;
            BtlObjPoolFree(p);
            a->sprites[i] = 0;
            i++;
        } while (i <= 0x7F);
    }
    a->spritesInUse = 0;
}

/* fn: sub_0806B064 */
// @ 0x0806b064
/* match-compiler: old_agbcc */

// @ 0x0806B064
// Width measure over the 0xDC-stride item array: skips a leading space run into
// `spaces`, adds 5 per extra space, accumulates each item's glyph width minus its
// kerning delta, then scales by unk24 and normalises by 8.
// The final `total = ...; return total;` is load-bearing: it keeps `total` live
// into the return and gives it one more reference than the struct pointer, which
// is what makes agbcc give r3 to `total` and r4 to the pointer (retail) instead
// of the reverse.
s32 AnimTextRowMeasure(struct AnimTextRow *a)
{
    struct AnimTextItem *item;
    s32 total;
    u16 spaces;
    u16 i;

    spaces = 0;
    total = 0;
    i = 0;
    for (; i < a->count; i++)
    {
        item = &a->items[i];
        if (a->text != 0 && a->text[i + spaces] == 0x20)
        {
            total += 5;
            spaces++;
        }
        if (item->visible != 0)
        {
            if (a->kernTable != 0)
                total += item->width - *((const u8 *)a->kernTable + item->frame);
            else
                total += item->width;
        }
    }
    total = (a->scale * total) >> 8;
    return total;
}

/* fn: sub_0806B2F0 */
// @ 0x0806b2f0
// Draws |value| right to left into the digit sprites of `row`, starting at
// slot `pos` and covering at most `count` slots. Leading zeroes are only
// drawn when `padZero` is set. Returns the number of digits drawn.
u16 DigitRowDraw(struct Unk6B2F0 *row, s32 value, u16 pos, u16 count, u8 padZero)
{
    struct Actor *obj;
    s16 drawn;
    s16 i;
    s32 digit;
    s32 n;

    drawn = 0;
    if (value < 0)
        value = -value;
    n = value;
    if ((s16)pos >= row->unk04)
        return 0;
    for (i = pos; i > (s16)pos - (s16)count; i--)
    {
        obj = &row->unk00[i];
        if (n > 0)
            digit = DivRemainder(n, 10);
        else
            digit = 0;
        if (digit == 0 && n == 0 && drawn != 0)
        {
            if (!padZero)
                break;
            obj->unk70 = (void *)-1;
            AnimObjSetRecordAt((struct AnimObjPlayback *)obj, 0, 0x34);
            drawn++;
        }
        else
        {
            obj->unk70 = (void *)-1;
            AnimObjSetRecordAt((struct AnimObjPlayback *)obj, 0, digit + 0x34);
            drawn++;
        }
        if (n > 0)
            n = Div(n, 10);
    }
    return drawn;
}

/* fn: sub_0806B3E8 */
// @ 0x0806b3e8

void AnimTextRowFill(struct AnimTextRow *a)
{
    u32 left;
    const u8 *text;
    struct AnimTextItem *item;
    u8 ch;
    s32 prev;

    left = a->count;
    text = a->text;
    item = a->items;
    goto check;
body:
    if (ch != 0x20)
    {
        AnimObjSetRecordAt((struct AnimObjPlayback *)item, 0, gData_080BB748[ch]);
        item->visible = -1;
        item++;
        left--;
    }
check:
    if (left == 0)
        goto zero;
    ch = *text;
    text++;
    if (ch != 0)
        goto body;
zero:
    prev = left;
    left--;
    if (prev == 0)
        goto done;
    do
    {
        item->visible = 0;
        item++;
        prev = left;
        left--;
    } while (prev != 0);
done:
    left = prev;
}

/* fn: sub_0806B5C8 */
// @ 0x0806b5c8
// ORs an 8-row 4bpp glyph from `src` into the 2x2 tile block at `tiles`,
// shifted right by x & 7 pixels and down by y & 7 rows. Columns that fall
// off the left (x < 0) or right (x >> 3 > 28) edge are clipped.
void GlyphBlit2x2(u16 *tiles, s32 base, u32 *src, s32 x, u32 y)
{
    u32 *tl, *tr, *bl, *br;
    s32 col;
    s32 shr;
    s32 n, m;
    u32 lo, hi;

    col = x >> 3;
    if (y > 0x98 || (u32)(x + 7) > 0xF6)
        return;
    tl = (u32 *)TileAddrFromIndex(base, tiles[0]);
    tr = (u32 *)TileAddrFromIndex(base, tiles[1]);
    bl = (u32 *)TileAddrFromIndex(base, tiles[0x20]);
    br = (u32 *)TileAddrFromIndex(base, tiles[0x21]);
    x &= 7;
    y &= 7;
    tl += y;
    tr += y;
    x *= 4;
    shr = 32 - x;
    n = 8 - y;
    m = y;
    while (--n != -1)
    {
        hi = *src++;
        lo = hi << x;
        hi >>= shr;
        if (col >= 0)
            *tl |= lo;
        if (col <= 28)
            *tr |= hi;
        tl++;
        tr++;
    }
    while (--m != -1)
    {
        hi = *src++;
        lo = hi << x;
        hi >>= shr;
        if (col >= 0)
            *bl |= lo;
        if (col <= 28)
            *br |= hi;
        bl++;
        br++;
    }
}

/* fn: sub_0806B764 */
// @ 0x0806b764
/* match-compiler: old_agbcc */

// @ 0x0806b764
// Lays `str` out on a tile-map text layer starting at pixel (x, y): claims and
// clears tile cells for the aligned string width, then blits each glyph into
// them. align: 1 = right-aligned at x, 2 = centred on x. Returns the pen x.
s32 TextLayerInit(struct TextLayer *a, s32 x, s32 y, u8 *str, u32 alignArg)
{
    u8 align = alignArg;
    struct TextWindow *win = a->win;
    struct Unk6BB38 *font = a->font;
    u16 *cur = (u16 *)(0x06000000 + (win->screenBlock << 11));
    u32 charBase = 0x06000000 + (win->charBlock << 14);
    u32 wt = font->unk04 >> 3;
    u32 ht = font->unk05 >> 3;
    u32 glyphAdv = font->unk04;
    s32 strW;
    s32 rows;
    s32 cols;
    u16 start;
    u32 c;
    vu16 *reg;
    int pin; /* pins the base+offset sum so agbcc adds charBlock<<14 last */

    reg = BgGetCntReg(win->bgIndex);
    if ((*reg & 0x80) || !(font->unk0C & 1))
    {
        DebugMessage((void *)0x083D1D08);
        return x;
    }
    strW = sub_0806B724(str, a->widths, glyphAdv);
    switch (align & 3)
    {
    case 1:
        x -= strW;
        break;
    case 2:
        x -= strW >> 1;
        break;
    }
    cur += (((y & ~7) << 2) + (x >> 3));
    rows = ht;
    if ((y & 7) != 0)
        rows++;
    cols = (strW + (x & 7) + 8) >> 3;
    start = a->nextTile;
    while (rows-- != 0)
    {
        s32 n = cols;

        while (n-- != 0)
        {
            if (*cur == 0)
            {
                *cur = a->nextTile;
                a->nextTile++;
            }
            *cur = (*cur & 0xFFF) | (a->palette << 12);
            cur++;
        }
        cur += 0x20 - cols;
    }
    {
        u32 n = a->nextTile - start;

        if (n != 0)
            ((void (*)(u32, u32, u32))gData_080BB8BC[0])(0, (a->win->charBlock << 14) + (pin = 0x06000000 + (start << 5)), n << 5);
    }
    cur = (u16 *)(0x06000000 + (win->screenBlock << 11));
    c = *str++;
    while (c != 0)
    {
        s32 adv = 5;

        if (c > 0x20)
        {
            s32 yy = y;
            s32 r = ht;
            u32 *glyph;

            c = gData_080BB748[c];
            glyph = TextLayerTileAddr(a->font, c);
            adv = glyphAdv;
            if (a->widths != NULL)
                adv -= a->widths[c];
            r--;
            if (ht != 0)
            {
                do
                {
                    s32 xx = x;
                    s32 n = wt - 1;

                    if (wt != 0)
                    {
                        u16 *row = (u16 *)((u8 *)cur + ((yy & ~7) << 3));

                        do
                        {
                            GlyphBlit2x2(row + (xx >> 3), charBase, glyph, xx, yy);
                            xx += 8;
                            glyph += 8;
                        } while (n-- != 0);
                    }
                    yy += 8;
                } while (r-- != 0);
            }
        }
        x += adv;
        if (x > 0xEF)
            break;
        c = *str++;
    }
    return x;
}

/* fn: sub_0806BB38 */
// @ 0x0806bb38
void *TextLayerTileAddr(struct Unk6BB38 *a, u32 idx)
{
    u8 bit;

    bit = a->unk06;
    return (u8 *)a + (idx << bit) + a->unk10;
}

/* fn: sub_080705DC */
// @ 0x080705dc
void TextEntrySetPaletteBank(struct Sprite *a, s32 b)
{
    u32 t;
    u32 v;
    u32 mask;

    t = b << 24;
    v = 0xFFF;
    v &= a->unk14;
    mask = 0xF0 << 20;
    mask &= t;
    mask >>= 12;
    a->unk14 = v | mask;
}

/* fn: sub_0807069C */
// @ 0x0807069c
void TextGroupClear(struct TextGroup *a)
{
    BtlObjPoolReleaseChain(&a->glyphs);
    a->penX = 0;
}

/* fn: sub_08070AF8 */
// @ 0x08070af8
/* match-compiler: old_agbcc */

// Points every glyph of the group at the shared affine object. Bit 9 (OAM
// double size) is set when the scale would clip the sprite, unless the group
// asks for no double size (unk08 bit 3).
#define GROUP_APPLY_AFFINE(g, aff)                                  \
    {                                                               \
        u32 bits = ((aff->unk08 & 0x3E0) << 20) | 0x100;            \
        struct Sprite *node = (struct Sprite *)g->glyphs.head;  \
        s32 n = g->glyphs.count;                                     \
        if (!(g->flags & 8))                                        \
        {                                                           \
            if (aff->angle != 0)                                    \
            {                                                       \
                if (aff->scaleX > 0xB0 || aff->scaleY > 0xB0)         \
                    bits |= 0x200;                                  \
            }                                                       \
            else if (aff->scaleX > 0x100 || aff->scaleY > 0x100)      \
                bits |= 0x200;                                      \
        }                                                           \
        for (n--; n != -1; n--)                                     \
        {                                                           \
            node->affine = (struct Sprite *)aff;                   \
            node->unk10 = (node->unk10 & 0xC1FFFCFF) | bits;        \
            node = node->next;                                     \
        }                                                           \
        AffineObjLock(aff);                                          \
    }

// Sets a text sprite group's scale (x, y): per glyph when the group scales its
// glyphs individually (unk08 bit 2), otherwise re-creates the shared affine
// object and patches every glyph's OAM affine index and double-size bit
// (cleared again if no affine slot is free).
void TextGroupSetScale(struct TextGroup *g, u16 x, u16 y)
{
    struct AffineObj *aff;

    if (g->glyphs.count == 0)
        return;
    if (g->flags & 4)
    {
        struct Sprite *node = (struct Sprite *)g->glyphs.head;
        s32 n;

        for (n = g->glyphs.count - 1; n != -1; n--)
        {
            sub_080703FC((struct Unk703FC *)node, x, y);
            node = node->next;
        }
    }
    else if ((aff = g->affine) != NULL)
    {
        AffineObjUnlock(aff);
        aff = g->affine = BtlObjSetAffine(aff, x, y, aff->angle);
        if (aff == NULL)
        {
            struct Sprite *node = (struct Sprite *)g->glyphs.head;
            s32 n = g->glyphs.count;

            for (n--; n != -1; n--)
            {
                node->affine = NULL;
                node->unk10 &= 0xC1FFFCFF;
                node = node->next;
            }
        }
        else
            GROUP_APPLY_AFFINE(g, aff)
    }
    else
    {
        aff = g->affine = BtlObjSetAffine(NULL, x, y, 0);
        if (aff != NULL)
            GROUP_APPLY_AFFINE(g, aff)
    }
    sub_080706B0((struct Unk70C98 *)g);
}

/* fn: sub_08070C98 */
// @ 0x08070c98
void TextGroupMoveBy(struct Unk70C98 *a, s32 b, s32 c)
{
    a->unk00 += (b << 16) >> 8;
    a->unk04 += (c << 16) >> 8;
    sub_080706B0(a);
}

/* fn: sub_08070D44 */
// @ 0x08070d44
/* match-compiler: old_agbcc */
u8 TextGroupAppendNumber(struct TextGroup *a, s32 value, u8 b)
{
    u8 buf[0x10];
    u32 neg;
    u8 commas;
    u8 digits;
    u8 *p;

    neg = 0;
    commas = 3;
    digits = 0x0E;
    if (value < 0) {
        neg = 1;
        value = -value;
    }
    p = buf + 15;
    *p = 0;
    do {
        if (value == 0) {
            *--p = 0x30;
            break;
        }
        if ((a->flags & 0x40) == 0) {
            commas--;
            if (commas == 0xFF) {
                *--p = 0x2C;
                commas = 2;
                digits--;
            }
        }
        *--p = (u8)DivRemainder(value, 10) + 0x30;
        value = Div(value, 10);
        digits--;
    } while (value != 0 && digits != 0);
    if (neg != 0)
        *--p = 0x2D;
    return TextGroupAppendString(a, p, b);
}

/* fn: sub_08070DF4 */
// @ 0x08070df4
u8 TextGroupSetNumber(struct TextGroup *a, void *b, u8 c)
{
    TextGroupClear(a);
    return TextGroupAppendNumber(a, (s32)b, c);
}

/* fn: sub_080712CC */
// @ 0x080712cc
void TextGroupSetObjMode(struct Unk712CC *a, u8 v)
{
    struct Sprite *p;
    s32 n;

    p = a->unk14;
    n = a->unk1C;
    n = n - 1;
    if (n != -1)
    {
        do
        {
            SpriteSetObjMode(p, v);
            p = p->next;
            n = n - 1;
        } while (n != -1);
    }
    a->unk0E = v;
}

/* fn: sub_080735DC */
// @ 0x080735dc
s32 StringCopy(u8 *src, u8 *dst, u32 n);

void TextFormatInt(s32 num, void *dst, u32 n)
{
    u8 buf[0x16];
    u32 sign;
    u8 pos;

    _08075A58(buf, gData_083D26F0, 0x16);
    pos = 0x14;
    sign = 1;
    if (num < 0) {
        num = -num;
        sign = 0;
    }
    if (num == 0)
        StringCopy(gData_083D2708, dst, n);
    else {
        while (num > 0) {
            u8 digit = DivRemainder(num, 10);
            u8 slot = pos;

            pos = (u8)(pos - 1);
            buf[slot] = digit + 0x30;
            num = Div(num, 10);
        }
        StringCopy(buf + pos + sign, dst, n);
    }
}

/* fn: sub_08073988 */
// @ 0x08073988
/* match-compiler: old_agbcc */

s32 TextMeasureWidth(const u8 *text_arg, const u8 *base_arg, u32 delta_arg, u32 space_arg)
{
    u32 index;
    u32 total;
    u32 ch;

    index = 0;
    total = 0;
    if (!text_arg)
        return 0;
    while (1) {
        ch = text_arg[index];
        index++;
        if (!ch)
            return total;
        switch (ch) {
        case 32:
            total += space_arg;
            break;
        case 7:
            index += 2;
            break;
        case 8:
            index += 1;
            break;
        case 10:
            break;
        default:
            total += delta_arg - base_arg[gData_080BB748[ch]];
            break;
        }
        if (!ch)
            return total;
    }
    return total;
}

/* fn: sub_080739E8 */
// @ 0x080739e8
/* match-compiler: old_agbcc */
// TRUE if the string contains '\n'. A NULL string falls off the end without a
// return (retail bug): r0 still holds the NULL argument, so it returns 0.
s32 TextHasNewline(u8 *s)
{
    u8 c;
    u32 i;

    if (s != NULL)
    {
        c = s[0];
        i = 1;
        while (c != 0)
        {
            if (c == '\n')
                return 1;
            c = s[i++];
        }
        return 0;
    }
}
