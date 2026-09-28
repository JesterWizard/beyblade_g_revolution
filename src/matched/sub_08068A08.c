#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068a08
/* match-compiler: old_agbcc */
// Initialises an affine BG layer from a resource header: like sub_08068BD4, but
// the map size, tile data and map pointers come from the header and the tiles
// are copied (not cleared) into the reserved char blocks.
void AffineBgLoad(struct Unk68E54 *st, u8 bg, void *resArg, u16 cnt, u16 mode)
{
    struct Unk68A08Res *res = resArg;
    u32 size;
    u8 flags;
    struct Unk688C8Rect *rect;
    u32 blocks;
    u32 n;
    u32 m;
    u16 *reg;

    st->unk68 = (s32)res;
    st->unk64 = res->shape;
    size = OamShapeToSize((struct Unk691E4 *)st, cnt, st->unk64);
    flags = res->flags;
    rect = &gData_03000008[bg];
    st->unk08 = rect;
    rect->unk10 = 0;
    rect->unk14 = 0;
    rect->unk00 = 0;
    rect->unk08 = (1 << st->unk5F) - 1;
    rect->unk04 = 0;
    rect->unk0C = (1 << st->unk60) - 1;
    st->unk00 = res->width;
    st->unk04 = res->height;
    st->unk5E = bg;
    st->unk0C = 0;
    st->unk10 = 0;
    st->unk14 = 0;
    st->unk18 = 0;
    st->unk1C = 0;
    st->unk20 = 0;
    st->unk54 = 0;
    st->unk58 = 0;
    st->unk24 = 0x10;
    st->unk40 = 0;
    st->unk44 = 0;
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
    st->unk74 = res->tilesSize;
    st->unk70 = (s32)((u8 *)res + res->mapOffset);
    st->unk78 = res->mapSize;
    blocks = (st->unk74 - 1) >> 14;
    st->unk5D = gData_03000108;
    st->unk61 = res->unk14;
    if (st->unk74 != 0)
    {
        ((void (*)(const void *, void *, u32))gData_080BB8C0[0])((void *)st->unk6C, (void *)(st->unk5D * 0x4000 + 0x06000000), st->unk74);
        gData_03000108 += 1 + blocks;
    }
    else
        st->unk5D = 0;
    if (((blocks + 1) << 14) - st->unk74 >= size && st->unk74 != 0)
    {
        n = size >> 11;
        m = n;
        if (n == 0)
            m = 1;
        st->unk5C = gData_03000108 * 8 - m;
        if (st->unk5C >= gData_030001A8 - n)
            st->unk5C = gData_030001A8 -= n;
    }
    else
    {
        st->unk5C = gData_030001A8 -= size >> 11;
    }
    reg = BgGetCntReg(bg);
    *reg = (st->unk5C << 8) | cnt | (st->unk5D << 2) | (((flags & 1) ^ 1) << 7);
}

