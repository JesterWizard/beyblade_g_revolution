#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806960c
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

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

