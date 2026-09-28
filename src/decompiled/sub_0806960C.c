/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void BgMapScroll(struct Unk68E54 *st, s32 dx, s32 dy)
{
    struct Unk688C8Rect v;
    s32 start[2];
    s32 cols, rows;
    s32 colCount, rowCount;
    u8 affine;
    u8 w, h;
    s32 x, y;
    struct Unk688C8Rect *rect;

    cols = 0;
    rows = 0;
    colCount = 0;
    rowCount = 0;
    affine = st->unk64 & 1;
    w = 1 << st->unk5F;
    h = 1 << st->unk60;
    x = st->unk0C += dx;
    y = st->unk10 += dy;
    st->unk40 += dx;
    st->unk44 += dy;
    v.unk00 = x >> 11;
    v.unk04 = y >> 11;
    v.unk08 = v.unk00 + 30;
    v.unk0C = v.unk04 + 20;
    rect = st->unk08;
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
        st->unk08->unk10 += cols;
        st->unk08->unk00 += cols;
        st->unk08->unk08 += cols;
        if (st->unk7C & 8)
        {
            if (st->unk08->unk08 >= st->unk00 && st->unk08->unk00 >= st->unk00)
            {
                st->unk08->unk00 -= st->unk00;
                st->unk08->unk08 -= st->unk00;
                st->unk08->unk10 &= (1 << st->unk5F) - 1;
                st->unk0C -= st->unk00 << 11;
            }
            else if (st->unk08->unk08 < 0 && st->unk08->unk00 < 0)
            {
                st->unk08->unk00 += st->unk00;
                st->unk08->unk08 += st->unk00;
                st->unk08->unk10 &= (1 << st->unk5F) - 1;
                st->unk0C += st->unk00 << 11;
            }
        }
    }
    if (rows != 0 && !(st->unk7C & 2))
    {
        BgMapBlitRect((struct Unk68988 *)st, st->unk08->unk00, start[1], st->unk08->unk10, v.unk14, 32, rowCount);
        st->unk08->unk14 += rows;
        st->unk08->unk04 += rows;
        st->unk08->unk0C += rows;
        if (st->unk7C & 4)
        {
            /* BUG: the top edge is tested against the map width. */
            if (st->unk08->unk0C >= st->unk04 && st->unk08->unk04 >= st->unk00)
            {
                st->unk08->unk04 -= st->unk04;
                st->unk08->unk0C -= st->unk04;
                st->unk10 -= st->unk04 << 11;
            }
            else if (st->unk08->unk0C < 0 && st->unk08->unk04 < 0)
            {
                st->unk08->unk04 += st->unk04;
                st->unk08->unk0C += st->unk04;
                st->unk10 += st->unk04 << 11;
            }
        }
    }
    if (!affine)
    {
        *BgGetHofsReg(st->unk5E) = st->unk40 >> 8;
        *BgGetVofsReg(st->unk5E) = st->unk44 >> 8;
    }
    else
        sub_080699C8(st->unk5E, st->unk40, st->unk44);
}
