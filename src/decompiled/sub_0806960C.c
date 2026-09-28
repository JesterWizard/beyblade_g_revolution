/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void BgMapScroll(struct MapLayer *st, s32 dx, s32 dy)
{
    struct MapTileRect v;
    s32 start[2];
    s32 cols, rows;
    s32 colCount, rowCount;
    u8 affine;
    u8 w, h;
    s32 x, y;
    struct MapTileRect *rect;

    cols = 0;
    rows = 0;
    colCount = 0;
    rowCount = 0;
    affine = st->unk64 & 1;
    w = 1 << st->log2Width;
    h = 1 << st->log2Height;
    x = st->scrollX += dx;
    y = st->scrollY += dy;
    st->offsetX += dx;
    st->offsetY += dy;
    v.unk00 = x >> 11;
    v.unk04 = y >> 11;
    v.unk08 = v.unk00 + 30;
    v.unk0C = v.unk04 + 20;
    rect = st->visible;
    if (v.unk08 > rect->unk08)
    {
        cols = v.unk08 - rect->unk08;
        v.unk10 = rect->unk10 + w;
        start[0] = rect->unk08 + 1;
        colCount = cols;
    }
    if (v.unk00 < rect->unk00)
    {
        cols = v.unk00 - rect->unk00;
        v.unk10 = rect->unk10 + cols;
        start[0] = rect->unk00 + cols;
        colCount = -cols;
    }
    if (v.unk0C > rect->unk0C)
    {
        rows = v.unk0C - rect->unk0C;
        v.unk14 = rect->unk14 + h;
        start[1] = rect->unk0C + 1;
        rowCount = rows;
    }
    if (v.unk04 < rect->unk04)
    {
        rows = v.unk04 - rect->unk04;
        v.unk14 = rect->unk14 + rows;
        start[1] = rect->unk04 + rows;
        rowCount = -rows;
    }
    if (cols != 0 && !(st->unk7C & 1))
    {
        BgMapBlitRect((struct Unk68988 *)st, start[0], rect->unk04, v.unk10, rect->unk14, colCount, 32);
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
        BgMapBlitRect((struct Unk68988 *)st, st->visible->unk00, start[1], st->visible->unk10, v.unk14, 32, rowCount);
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
