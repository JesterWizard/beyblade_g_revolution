#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_08060C30 */
// @ 0x08060c30
/* match-compiler: old_agbcc */
// Window setup on an explicit window (cf. sub_0806121C for gData_03000798):
// clear it, record source and count, then lay out (sub_08060D58) and finish
// (sub_08060D28).
void TextWindowOpenEx(void *winArg, void *srcArg, void *c, u16 count, u16 y, u16 h, u16 x, u16 w, u16 i, u8 mode)
{
    struct TextWindow *win = winArg;
    struct Unk617C4 *src = srcArg;
    u16 attr = i << 12;

    ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, win, 0xAC);
    win->unk88 = src;
    win->widthTable = (u32)c;
    win->tileCount = count;
    win->baseTile = attr;
    win->glyphWidth = src->unk04;
    win->lineHeight = src->unk05;
    win->penX = 0;
    win->penY = 0;
    win->spacing = win->glyphWidth >> 2;
    win->unkA4 = 0;
    win->unkA6 = 0;
    AffineBgInit((struct MapLayer *)win, mode, count, 0);
    TextWindowFillMap(win, (u8)x, (u8)w, (u8)y, (u8)h, (u16)(count - 1));
    TextWindowClearTiles(win);
}

/* fn: sub_08060D28 */
// @ 0x08060d28

void TextWindowClearTiles(struct TextWindow *a)
{
    void **fn;
    void *dst;
    u32 n;
    u32 tmp;

    if (a != 0)
    {
        fn = (void **)0x080BB8BC;
        tmp = a->charBlock;
        dst = (void *)((tmp << 14) + (0xC0u << 19));
        tmp = a->tileCount;
        n = tmp << 5;
        _08073C4C((void *)0, dst, n, *fn);
    }
}

/* fn: sub_08060D58 */
// @ 0x08060d58
/* match-compiler: old_agbcc */
// Fill the BG screen block with the fill pattern, then lay a width x height
// run of consecutive tile ids (| baseTile) at (x, y) and record the window.
void TextWindowFillMap(struct TextWindow *state, u32 x_arg, u32 y_arg, u32 w_arg, u32 h_arg, u32 tile_arg)
{
    u8 x = x_arg;
    u8 y = y_arg;
    u8 width = w_arg;
    u8 height = h_arg;
    u16 tile = tile_arg;
    u16 tileId;
    u16 baseTile;
    u16 *vram;
    u16 row;
    u16 col;
    u32 *fillSrc;

    tileId = 0;
    baseTile = state->baseTile;
    vram = (u16 *)(VRAM + (state->screenBlock << 11));
    fillSrc = gData_080BB8BC;
    _08073C4C((void *)(tile | (tile << 16) | baseTile), vram, 0x800, (void *)*fillSrc);
    vram += (y << 5) + x;
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            vram[row * 32 + col] = tileId | baseTile;
            tileId++;
        }
    }
    state->width = width << 3;
    state->height = height << 3;
    state->unkA4 = x;
    state->unkA6 = y;
}

/* fn: sub_08060E48 */
// @ 0x08060e48
/* match-compiler: old_agbcc */
// Draw one glyph of `chArg` at the window's pen: point the tilemap cells the
// glyph covers at the window's tiles (baseTile palette bits), OR the 4bpp glyph
// rows into the tile graphics shifted by the pen's sub-tile x offset (spilling
// into the next tile column), then advance penX. A space only advances by
// `spacing`; glyphs that would cross the window edge are skipped.
void TextWindowPutChar(struct TextWindow *w, u32 chArg)
{
    u8 ch;
    u32 sx;
    s32 xt;
    u32 unkA6;
    u32 *glyph;
    u32 mapBase;
    u32 gw;
    u32 rows;
    s32 yt;

    ch = chArg;
    if (ch == 0x20)
    {
        w->penX += w->spacing;
        return;
    }
    gw = w->glyphWidth;
    rows = w->lineHeight;
    ch = gData_080BB748[ch];
    glyph = TextLayerTileAddr(w->unk88, ch);
    if ((u32)((s16)w->penX + (gw - ((u8 *)w->widthTable)[ch])) >= w->width)
        return;
    if ((s16)w->penY >= w->height)
        return;
    if (w->lineHeight + (s16)w->penY >= w->height)
        return;

    xt = ((s16)w->penX >> 3) << 5;
    yt = (s16)w->penY >> 3;
    unkA6 = w->unkA6;
    sx = w->penX & 7;
    mapBase = 0x06000000 + (w->screenBlock << 11);

    do
    {
        u32 *t = (u32 *)((u8 *)(w->charBlock << 14) + (xt + 0x06000000) + ((w->width >> 3) << 5) * yt);
        s32 col = w->unkA4;

        do
        {
            u32 k;
            u16 *map = (u16 *)(((yt + unkA6) << 6) + mapBase);

            map[((s16)w->penX >> 3) + col] &= 0xFFF;
            map[((s16)w->penX >> 3) + col] |= w->baseTile;
            if (sx != 0)
            {
                map[((s16)w->penX >> 3) + col + 1] &= 0xFFF;
                map[((s16)w->penX >> 3) + col + 1] |= w->baseTile;
            }
            for (k = 0; k < 4; k++)
            {
                u32 v, hi;
                u32 shl = sx * 4;
                u32 rsh = (8 - sx) * 4;

                v = *glyph++;
                hi = v;
                v <<= shl;
                hi >>= rsh;
                t[0] |= v;
                t[8] |= hi;
                t++;
                v = *glyph++;
                hi = v;
                v <<= shl;
                hi >>= rsh;
                t[0] |= v;
                t[8] |= hi;
                t++;
            }
            gw -= 8;
            col++;
        } while (gw != 0);
        rows -= 8;
        yt++;
        gw = w->glyphWidth;
    } while (rows != 0);
    w->penX += gw - ((u8 *)w->widthTable)[ch];
}

/* fn: sub_080611F0 */
// @ 0x080611f0
void TextWindowClose(void)
{
    void *p;

    VramSlotsRelease();
    p = *(void **)gUnk_03000790;
    if (p != 0)
    {
        HeapFree(p);
        *(void **)gUnk_03000790 = 0;
    }
    gUnk_03000798 = 0;
}

/* fn: sub_0806121C */
// @ 0x0806121c
/* match-compiler: old_agbcc */
// Set up the gData_03000798 window: clear it, record the source and count,
// lay out its tile block (sub_08061628) and finish with sub_08061308.
void TextWindowOpen(struct Unk617C4 *src, u32 b, u16 count, u16 c, u16 d, u16 e, u16 f, u16 g)
{
    u16 attr;
    struct TextWindow *st;

    attr = g << 12;
    ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, gData_03000798, 0xAC);
    st = gData_03000798;
    st->unk88 = src;
    st->widthTable = b;
    st->tileCount = count;
    st->baseTile = attr;
    st->glyphWidth = src->unk04;
    st->lineHeight = src->unk05;
    st->penX = 0;
    st->penY = 0;
    st->spacing = st->glyphWidth >> 2;
    st->unkA4 = 0;
    st->unkA6 = 0;
    AffineBgInit((struct MapLayer *)st, 3, count, 0);
    TextWindowLayout((u8)e, (u8)f, (u8)c, (u8)d, (u16)(count - 1));
    TextWindowClearActiveTiles();
}

/* fn: sub_08061308 */
// @ 0x08061308
/* match-compiler: old_agbcc */
void TextWindowClearActiveTiles(void)
{
    struct TextWindow *s;
    void **fn;
    void *dst;
    u32 n;
    u16 tmp;

    fn = (void **)0x080BB8BC;
    s = gUnk_03000798;
    tmp = s->charBlock;
    dst = (void *)((tmp << 14) + (0xC0u << 19));
    tmp = s->tileCount;
    n = tmp << 5;
    _08073C4C((void *)0, dst, n, *fn);
}

/* fn: sub_08061628 */
// @ 0x08061628
/* match-compiler: old_agbcc */
// Fill the window's BG map (screenblock unk5C) with the fill tile, then lay
// out a w x h block of consecutive tiles at (x, y) and record its pixel size
// and position.
void TextWindowLayout(u32 xArg, u32 yArg, u32 wArg, u32 hArg, u32 fillArg)
{
    u8 x = xArg;
    u8 y = yArg;
    u8 w = wArg;
    u8 h = hArg;
    u32 fill = fillArg << 16;
    u16 tile;
    u16 base;
    u16 *map;
    u16 row, col;

    tile = 0;
    base = gData_03000798->baseTile;
    map = (u16 *)(gData_03000798->screenBlock * 0x800 + 0x06000000);
    ((void (*)(u32, void *, u32))gData_080BB8BC[0])((fill >> 16) | fill | base, map, 0x800);
    map += y * 32 + x;
    for (row = 0; row < h; row++)
    {
        for (col = 0; col < w; col++)
        {
            map[row * 32 + col] = tile | base;
            tile++;
        }
    }
    gData_03000798->width = w << 3;
    gData_03000798->height = h << 3;
    gData_03000798->unkA4 = x;
    gData_03000798->unkA6 = y;
}

/* fn: sub_08061800 */
// @ 0x08061800
/* match-compiler: old_agbcc */
// `off = arg0 * stride + 0x06000000` must be a separate local: retail forms
// `arg0*stride + 0x06000000` first and adds `lo` last, while left-associating
// the sum in one expression makes agbcc accumulate `lo + arg0*stride` first.
void TextWindowClearRow(u16 arg0)
{
    struct TextWindow *p = gUnk_03000798;
    s32 lo;
    u16 h;
    s32 stride;
    s32 off;

    if (arg0 >= (p->height >> 3) - 1)
        return;

    lo = (s32)p->charBlock;
    lo <<= 0xE;
    h = p->width;
    stride = (h >> 3) << 5;
    off = arg0 * stride + 0x06000000;
    _08073C4C((void *)0, (void *)(lo + off), stride, *(void **)0x080BB8BC);
}

/* fn: sub_08061BE8 */
// @ 0x08061be8
void TextWindowPopState(void)
{
    u32 r0;
    u32 r1;
    struct TextWindow *r2;
    u32 r3;
    struct TextWindow **loc;
    struct Unk0770 *entry;
    void **handler_slot;

    r0 = gData_03000794[0] - 1;
    if ((s32)r0 < 0)
        return;

    r1 = (u32)gData_03000770;
    r0 <<= 3;
    entry = (struct Unk0770 *)(r0 + r1);
    handler_slot = (void **)entry->unk00;
    if (handler_slot == 0)
        return;

    loc = &gData_03000798;
    r2 = *loc;
    r0 = (u32)r2 + 0x5D;
    r0 = *(u8 *)r0;
    r1 = r0 << 14;
    r0 = 0xC0;
    r0 <<= 19;
    r1 += r0;
    r3 = (u32)gData_080BB8C0;
    r0 = (u32)*handler_slot;
    r2 = (struct TextWindow *)((u32)r2 + 0x94);
    r2 = (struct TextWindow *)(u32)*(u16 *)r2;
    r2 = (struct TextWindow *)((u32)r2 << 5);
    r3 = *(u32 *)r3;
    _08073C4C((void *)r0, (void *)r1, (u32)r2, (void *)r3);

    r1 = (u32)*loc;
    r2 = (struct TextWindow *)(u32)entry->unk04;
    r0 = r1 + 0x90;
    *(u16 *)r0 = (u16)(u32)r2;
    r0 = entry->unk06;
    r1 += 0x92;
    *(u16 *)r1 = (u16)r0;
}

/* fn: sub_08061DC0 */
// @ 0x08061dc0
/* match-compiler: old_agbcc */
// Two VRAM addresses (common base + per-arg scaled offset) handed to the
// bx-r3 trampoline _08073C4C with the stride and a table entry.
// `a0 = lo + b0` must be materialised before `b1` is computed: retail serialises
// addr0 fully before it starts addr1, so the first `add lo` cannot be sunk.
void TextWindowCopyRow(u16 arg0, u16 arg1)
{
    s32 stride;
    s32 lo;
    u32 b0;
    u32 b1;
    void *a0;

    stride = (gUnk_03000798->width >> 3) << 5;
    lo = gUnk_03000798->charBlock << 0xE;
    b0 = arg0 * stride + 0x06000000;
    a0 = (void *)(lo + b0);
    b1 = arg1 * stride + 0x06000000;
    _08073C4C(a0, (void *)(lo + b1), stride, *(void **)0x080BB8C0);
}
