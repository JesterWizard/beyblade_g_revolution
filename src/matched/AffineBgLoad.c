#include "global.h"
#include "ram_map.h"
#include "battle.h"

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

