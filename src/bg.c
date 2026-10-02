#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_080688C8 */
// @ 0x080688c8
// Load a BG tile map, set the scroll registers to (x, y), and seed the
// visible tile rect (x/8, y/8, width 1<<unk5F, height 1<<unk60).
void BgMapInit(struct Unk68988 *state, u8 index, void *arg2, u16 limit, u16 mode, s32 x, s32 y)
{
    struct MapTileRect *rect;
    s32 xt = x >> 3;
    s32 yt = y >> 3;
    s32 w, h;

    AffineBgLoad((struct MapLayer *)state, index, arg2, limit, mode);
    *BgGetHofsReg(index) = x;
    *BgGetVofsReg(index) = y;
    rect = state->unk08;
    rect->unk10 = xt;
    rect->unk14 = yt;
    rect->unk00 = xt;
    rect->unk08 = xt + (1 << state->unk5F) - 1;
    rect->unk04 = yt;
    rect->unk0C = yt + (1 << state->unk60) - 1;
    state->unk0C = x << 8;
    state->unk10 = y << 8;
    state->unk40 = x << 8;
    state->unk44 = y << 8;
    w = 1 << state->unk5F;
    h = 1 << state->unk60;
    if (!(mode & 2))
        BgMapBlitRect(state, rect->unk00, rect->unk04, rect->unk10, rect->unk14, w, h);
}

/* fn: sub_08068A08 */
// @ 0x08068a08
/* match-compiler: old_agbcc */
// Initialises an affine BG layer from a resource header: like sub_08068BD4, but
// the map size, tile data and map pointers come from the header and the tiles
// are copied (not cleared) into the reserved char blocks.
void AffineBgLoad(struct MapLayer *st, u8 bg, void *resArg, u16 cnt, u16 mode)
{
    struct AffineBgResource *res = resArg;
    u32 size;
    u8 flags;
    struct MapTileRect *rect;
    u32 blocks;
    u32 n;
    u32 m;
    u16 *reg;

    st->unk68 = (s32)res;
    st->unk64 = res->shape;
    size = OamShapeToSize((struct Unk691E4 *)st, cnt, st->unk64);
    flags = res->flags;
    rect = &gData_03000008[bg];
    st->visible = rect;
    rect->unk10 = 0;
    rect->unk14 = 0;
    rect->unk00 = 0;
    rect->unk08 = (1 << st->log2Width) - 1;
    rect->unk04 = 0;
    rect->unk0C = (1 << st->log2Height) - 1;
    st->widthTiles = res->width;
    st->heightTiles = res->height;
    st->bgId = bg;
    st->scrollX = 0;
    st->scrollY = 0;
    st->deltaX = 0;
    st->deltaY = 0;
    st->unk1C = 0;
    st->unk20 = 0;
    st->unk54 = 0;
    st->unk58 = 0;
    st->unk24 = 0x10;
    st->offsetX = 0;
    st->offsetY = 0;
    st->unk28 = 0;
    st->unk2C = 0;
    st->unk30 = 0x10000;
    st->unk34 = 0x10000;
    st->unk38 = 0;
    st->unk3C = 0;
    st->unk48 = 0;
    st->unk4A = 0;
    st->unk4C = 0;
    st->unk50 = 0;
    st->unk7C = mode & 0x0C;
    st->unk80 = -1;
    st->unk84 = 0;
    st->unk6C = (s32)((u8 *)res + res->tilesOffset);
    st->tileBytes = res->tilesSize;
    st->unk70 = (s32)((u8 *)res + res->mapOffset);
    st->unk78 = res->mapSize;
    blocks = (st->tileBytes - 1) >> 14;
    st->charBlock = gData_03000108;
    st->unk61 = res->unk14;
    if (st->tileBytes != 0)
    {
        ((void (*)(const void *, void *, u32))gData_080BB8C0[0])((void *)st->unk6C, (void *)(st->charBlock * 0x4000 + 0x06000000), st->tileBytes);
        gData_03000108 += 1 + blocks;
    }
    else
        st->charBlock = 0;
    if (((blocks + 1) << 14) - st->tileBytes >= size && st->tileBytes != 0)
    {
        n = size >> 11;
        m = n;
        if (n == 0)
            m = 1;
        st->screenBlock = gData_03000108 * 8 - m;
        if (st->screenBlock >= gData_030001A8 - n)
            st->screenBlock = gData_030001A8 -= n;
    }
    else
    {
        st->screenBlock = gData_030001A8 -= size >> 11;
    }
    reg = BgGetCntReg(bg);
    *reg = (st->screenBlock << 8) | cnt | (st->charBlock << 2) | (((flags & 1) ^ 1) << 7);
}

/* fn: sub_08068BD4 */
// @ 0x08068bd4
/* match-compiler: old_agbcc */
// Initialises an affine BG layer: resets the scroll/scale state, points it at
// its visible-rect slot, reserves char blocks (gData_03000108 grows upwards)
// and screen blocks (gData_030001A8 grows downwards) for the tile data,
// clears that VRAM and writes the BGxCNT value.
void AffineBgInit(struct MapLayer *st, u8 bg, u16 tiles, u16 cnt)
{
    u32 size;
    struct MapTileRect *rect;
    u32 blocks;
    u32 n;
    u32 m;
    u16 *reg;
    void *vram;

    st->unk68 = 0;
    st->unk64 = 0;
    size = OamShapeToSize((struct Unk691E4 *)st, cnt, 0);
    rect = &gData_03000008[bg];
    st->visible = rect;
    rect->unk10 = 0;
    rect->unk14 = 0;
    rect->unk00 = 0;
    rect->unk08 = (1 << st->log2Width) - 1;
    rect->unk04 = 0;
    rect->unk0C = (1 << st->log2Height) - 1;
    st->widthTiles = 0x20;
    st->heightTiles = 0x20;
    st->bgId = bg;
    st->scrollX = 0;
    st->scrollY = 0;
    st->deltaX = 0;
    st->deltaY = 0;
    st->unk1C = 0;
    st->unk20 = 0;
    st->unk54 = 0;
    st->unk58 = 0;
    st->unk24 = 0x10;
    st->offsetX = 0;
    st->offsetY = 0;
    st->unk28 = 0;
    st->unk2C = 0;
    st->unk30 = 0x10000;
    st->unk34 = 0x10000;
    st->unk38 = 0;
    st->unk3C = 0;
    st->unk48 = 0;
    st->unk4A = 0;
    st->unk4C = 0;
    st->unk50 = 0;
    st->unk7C = 0;
    st->unk80 = -1;
    st->unk84 = 0;
    st->unk6C = 0;
    if (cnt & 0x80)
        st->tileBytes = tiles << 6;
    else
        st->tileBytes = tiles << 5;
    st->unk70 = 0;
    st->unk78 = 0;
    blocks = (st->tileBytes - 1) >> 14;
    st->charBlock = gData_03000108;
    if (st->tileBytes != 0)
        gData_03000108 += 1 + blocks;
    else
        st->charBlock = 0;
    if (((blocks + 1) << 14) - st->tileBytes >= size && st->tileBytes != 0)
    {
        n = size >> 11;
        m = n;
        if (n == 0)
            m = 1;
        st->screenBlock = gData_03000108 * 8 - m;
        if (st->screenBlock >= gData_030001A8 - n)
            st->screenBlock = gData_030001A8 -= n;
    }
    else
    {
        st->screenBlock = gData_030001A8 -= size >> 11;
    }
    vram = (void *)(st->screenBlock * 0x800 + 0x06000000);
    ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, vram, size);
    reg = BgGetCntReg(bg);
    *reg = (st->screenBlock << 8) | cnt | (st->charBlock << 2);
}

/* fn: sub_08068EC0 */
// @ 0x08068ec0
// Per-frame affine BG update: advance the rotation angle (wrapping at
// 0x10000) and the unk30/unk34 pair by their velocities, rebuild the BG's
// matrix (sub_08069A60) and reference point (sub_080699C8), then damp the
// velocities by unk24/256, snapping any that stop shrinking to zero.
void AffineBgUpdate(void *arg)
{
    struct MapLayer *st = arg;
    u8 slot;
    s32 angle;
    s32 x, y;
    s32 damp;
    s32 dA, dX, dY;

    slot = st->bgId - 2;
    angle = st->unk28 + st->unk2C;
    st->unk28 = angle;
    if (angle < 0)
        st->unk28 = angle + 0x10000;
    x = st->unk30 + st->unk38;
    st->unk30 = x;
    y = st->unk34 + st->unk3C;
    st->unk34 = y;
    BgAffineSetRotScale(st->bgId, (u8)(st->unk28 >> 8), (u16)(x >> 8), (u16)(y >> 8));
    BgAffineSetRefPoint(st->bgId,
                 st->unk4C - (gData_03000068[slot].unk08 * st->unk48 - gData_03000068[slot].unk10 * st->unk4A),
                 st->unk50 + (st->unk48 * gData_03000068[slot].unk0C - gData_03000068[slot].unk14 * st->unk4A));
    damp = st->unk24;
    if (damp != 0)
    {
        dA = (st->unk2C * damp) >> 8;
        dX = (st->unk38 * damp) >> 8;
        dY = (st->unk3C * damp) >> 8;
        st->unk2C -= dA;
        st->unk38 -= dX;
        st->unk3C -= dY;
        if (dA == 0 && st->unk2C != 0)
            st->unk2C = 0;
        if (dX == 0 && st->unk38 != 0)
            st->unk38 = 0;
        if (dY == 0 && st->unk3C != 0)
            st->unk3C = 0;
    }
}

/* fn: sub_08069270 */
// @ 0x08069270
/* match-compiler: old_agbcc */
typedef void (*BlitFunc)(struct Unk68988 *, s32, s32, s32, s32, s32, s32);
typedef void (*BlitColFunc)(struct Unk68988 *, s32, s32, s32, s32);
void BgMapBlitRect(struct Unk68988 *st, s32 x, s32 y, s32 d, s32 e, s32 w, s32 h)
{
    BlitFunc blit;
    s32 h2;
    s32 x2;
    s32 e2;
    s32 len1;
    s32 len2;
    s32 d2;
    s32 end;
    s32 e1;
    s32 h1;

    len1 = w;
    h1 = h;
    len2 = 0;
    h2 = h;
    e1 = e;
    do { d2 = d; } while (0); /* extra ref weight keeps d in r3 */
    e2 = e;
    if (st->unk64 & 1)
        blit = (BlitFunc)0x0806945D;
    else
        blit = (BlitFunc)gData_080BB8A4[0];
    if (x + w > st->unk00)
    {
        len1 = 0;
        if (x < st->unk00)
            len1 = st->unk00 - x;
        len2 = w - len1;
        x2 = x + len1 - st->unk00;
        d2 += len1;
    }
    if (x < 0)
    {
        len1 = x + w;
        if (len1 < 0)
            len1 = 0;
        len2 = w - len1;
        x2 = x + st->unk00;
        x = 0;
        d += len2;
    }
    if (len1 > 0)
        blit(st, x, y, d, e1, len1, h1);
    if (len2 > 0)
    {
        if (st->unk7C & 8)
            blit(st, x2, y, d2, e2, len2, h2);
        else
            ((BlitColFunc)gData_080BB8A8[0])(st, d2, e2, len2, h2);
    }
}

/* fn: sub_0806960C */
// @ 0x0806960c
/* match-compiler: old_agbcc */

void BgMapScroll(struct MapLayer *st, s32 dx, s32 dy)
{
    struct { s32 x0, y0, x1, y1; } v;
    s32 sx, sy, ax, ay;
    s32 cols, rows;
    s32 colCount, rowCount;
    u8 affine;
    u8 *pw;
    u8 w, h;
    s32 x, y, tx, ty, k, k2;
    struct MapTileRect *rect;

    cols = 0;
    rows = 0;
    colCount = 0;
    rowCount = 0;
    affine = st->unk64 & 1;
    pw = &st->log2Width;
    w = 1 << *pw;
    h = 1 << st->log2Height;
    x = st->scrollX += dx;
    y = st->scrollY += dy;
    st->offsetX += dx;
    st->offsetY += dy;
    tx = x >> 11;
    ty = y >> 11;
    v.x0 = tx;
    v.y0 = ty;
    v.x1 = v.x0 + 30;
    v.y1 = v.y0 + 20;
    rect = st->visible;
    if (v.x1 > rect->unk08)
    {
        cols = v.x1 - rect->unk08;
        sx = rect->unk10 + w;
        ax = rect->unk08 + 1;
        colCount = cols;
    }
    if (v.x0 < rect->unk00)
    {
        cols = v.x0 - rect->unk00;
        sx = rect->unk10 + cols;
        ax = rect->unk00 + cols;
        colCount = -cols;
    }
    if (v.y1 > rect->unk0C)
    {
        rows = v.y1 - rect->unk0C;
        sy = rect->unk14 + h;
        ay = rect->unk0C + 1;
        rowCount = rows;
    }
    if (v.y0 < rect->unk04)
    {
        rows = v.y0 - rect->unk04;
        sy = rect->unk14 + rows;
        ay = rect->unk04 + rows;
        rowCount = -rows;
    }
    if (cols != 0 && !(st->unk7C & 1))
    {
        k = 32;
        BgMapBlitRect((struct Unk68988 *)st, ax, rect->unk04, sx, rect->unk14, colCount, k);
        st->visible->unk10 += cols;
        st->visible->unk00 += cols;
        st->visible->unk08 += cols;
        if (st->unk7C & 8)
        {
            if (st->visible->unk08 >= st->widthTiles && st->visible->unk00 >= st->widthTiles)
            {
                st->visible->unk00 -= st->widthTiles;
                st->visible->unk08 -= st->widthTiles;
                st->visible->unk10 &= (1 << st->log2Width) - 1;
                st->scrollX -= st->widthTiles << 11;
            }
            else if (st->visible->unk08 < 0 && st->visible->unk00 < 0)
            {
                st->visible->unk00 += st->widthTiles;
                st->visible->unk08 += st->widthTiles;
                st->visible->unk10 &= (1 << st->log2Width) - 1;
                st->scrollX += st->widthTiles << 11;
            }
        }
    }
    if (rows != 0 && !(st->unk7C & 2))
    {
        k2 = 32;
        BgMapBlitRect((struct Unk68988 *)st, st->visible->unk00, ay, st->visible->unk10, sy, k2, rowCount);
        st->visible->unk14 += rows;
        st->visible->unk04 += rows;
        st->visible->unk0C += rows;
        if (st->unk7C & 4)
        {
            /* BUG: the top edge is tested against the map width. */
            if (st->visible->unk0C >= st->heightTiles && st->visible->unk04 >= st->widthTiles)
            {
                st->visible->unk04 -= st->heightTiles;
                st->visible->unk0C -= st->heightTiles;
                st->scrollY -= st->heightTiles << 11;
            }
            else if (st->visible->unk0C < 0 && st->visible->unk04 < 0)
            {
                st->visible->unk04 += st->heightTiles;
                st->visible->unk0C += st->heightTiles;
                st->scrollY += st->heightTiles << 11;
            }
        }
    }
    if (!affine)
    {
        *BgGetHofsReg(st->bgId) = st->offsetX >> 8;
        *BgGetVofsReg(st->bgId) = st->offsetY >> 8;
    }
    else
        BgAffineSetRefPoint(st->bgId, st->offsetX, st->offsetY);
}

/* fn: sub_08069894 */
// @ 0x08069894

// @ 0x08069894
// Clear two byte flags, set a third to 0x20, zero four entries of the two
// per-index arrays, then kick two transfers with n = 0x100.
// The three destinations must be *distinct symbols* (gData_03000108 /
// gData_030001B0 / gData_030001A8 -- see asm/data_symbols.s): as bare literals
// agbcc folds the second address into `add r0, #0xA8` and hoists all three pool
// loads up front, losing retail's interleaved load/store shape.
void BgScrollReset(void)
{
    u8 i;
    u16 zero;
    u32 n;

    gData_03000108 = 0;
    gData_030001B0 = 0;
    gData_030001A8 = 0x20;

    i = 0;
    zero = 0;
    while (i <= 3)
    {
        *BgGetHofsReg(i) = zero;
        *BgGetVofsReg(i) = zero;
        i = (u8)(i + 1);
    }

    n = 0x80;
    n <<= 1;
    BgAffineSetRotScale(2, 0, n, n);
    BgAffineSetRotScale(3, 0, n, n);
}

/* fn: sub_08069908 */
// @ 0x08069908
/* match-compiler: old_agbcc */
u16 *BgGetHofsReg(u8 sel)
{
    switch (sel)
    {
    case 0: return (u16 *)0x04000010;
    case 1: return (u16 *)0x04000014;
    case 2: return (u16 *)0x04000018;
    case 3: return (u16 *)0x0400001C;
    }
}

/* fn: sub_08069948 */
// @ 0x08069948
/* match-compiler: old_agbcc */
u16 *BgGetVofsReg(u8 sel)
{
    switch (sel)
    {
    case 0: return (u16 *)0x04000012;
    case 1: return (u16 *)0x04000016;
    case 2: return (u16 *)0x0400001A;
    case 3: return (u16 *)0x0400001E;
    }
}

/* fn: sub_08069988 */
// @ 0x08069988
/* match-flags: -fprologue-bugfix */
void *BgGetCntReg(u8 a)
{
  u32 r0;
  unsigned short r1;
  u32 *new_var;
  new_var = &r0;
  r0 = a;
  r1 = *new_var;
  if ((*new_var) == 1)
  {
    goto case1;
  }
  if (((s32) r0) > 1)
  {
    goto high;
  }
  if (r0 == 0)
  {
    goto case0;
  }
  goto done;
  high:
  if (r1 == 2)
  {
    goto case2;
  }

  if (r1 == 3)
  {
    goto case3;
  }
  goto done;
  case0:
  r0 = 0x04000008;

  goto done;
  case1:
  r0 = 0x0400000A;

  goto done;
  case2:
  r0 = 0x0400000C;

  goto done;
  case3:
  r0 = 0x0400000E;

  done:
  return (void *) r0;

}

/* fn: sub_080699C8 */
// @ 0x080699c8
/* match-flags: -fprologue-bugfix */

void BgAffineSetRefPoint(u32 bg, s32 x, s32 y)
{
    switch ((u8)bg)
    {
    case 2:
        REG_BG2X_L = x;
        REG_BG2X_H = x >> 16;
        REG_BG2Y_L = y;
        REG_BG2Y_H = y >> 16;
        break;
    case 3:
        REG_BG3X_L = x;
        REG_BG3X_H = x >> 16;
        REG_BG3Y_L = y;
        REG_BG3Y_H = y >> 16;
        break;
    }
}

/* fn: sub_08069A18 */
// @ 0x08069a18

void BgAffineSetMatrix(u8 a, s16 b, s16 c, s16 d, s16 e)
{
    volatile u16 *reg;

    switch (a)
    {
    case 2:
        reg = (volatile u16 *)0x04000020;
        break;
    case 3:
        reg = (volatile u16 *)0x04000030;
        break;
    default:
        return;
    }

    *reg = b;
    reg++;
    *reg = c;
    reg++;
    *reg = d;
    reg++;
    *reg = e;
}

/* fn: sub_08069A60 */
// @ 0x08069a60
/* match-compiler: old_agbcc */
// Sets the rotation/scale matrix for affine BG `bg` (2 or 3): stores the angle
// and scale indices in its slot, builds PA..PD from the sine table and the
// reciprocal scale table, and writes them to the BG's affine registers.
void BgAffineSetRotScale(u8 bg, u8 angle, u16 scaleX, u16 scaleY)
{
    struct Unk0068Entry *e;
    u8 slot = bg - 2;

    if (slot > 2)
        return;
    gData_03000068[slot].unk02 = scaleX;
    gData_03000068[slot].unk04 = scaleY;
    gData_03000068[slot].unk00 = angle;
    e = &gData_03000068[slot];
    gData_03000068[slot].unk08 = (s16)FixedMulQ8(gData_083C9544[angle + 0x40], gData_083A9544[e->unk02]);
    gData_03000068[slot].unk0C = (s16)FixedMulQ8(gData_083C9544[e->unk00], gData_083A9544[e->unk02]);
    gData_03000068[slot].unk10 = (s16)FixedMulQ8(-gData_083C9544[e->unk00], gData_083A9544[e->unk04]);
    gData_03000068[slot].unk14 = (s16)FixedMulQ8(gData_083C9544[e->unk00 + 0x40], gData_083A9544[e->unk04]);
    BgAffineSetMatrix(bg, gData_03000068[slot].unk08, gData_03000068[slot].unk0C, gData_03000068[slot].unk10, gData_03000068[slot].unk14);
}

/* fn: sub_08069B78 */
// @ 0x08069b78
/* match-compiler: old_agbcc */
// Set the priority of BG0-BG3 (sub_08069988 returns the BGxCNT register).
void BgSetPriorities(u32 a, u32 b, u32 c, u32 d)
{
    u8 bg0 = a;
    u8 bg1 = b;
    u8 bg2 = c;
    u8 bg3 = d;

    ((struct BgCnt *)BgGetCntReg(0))->priority = bg0;
    ((struct BgCnt *)BgGetCntReg(1))->priority = bg1;
    ((struct BgCnt *)BgGetCntReg(2))->priority = bg2;
    ((struct BgCnt *)BgGetCntReg(3))->priority = bg3;
}
