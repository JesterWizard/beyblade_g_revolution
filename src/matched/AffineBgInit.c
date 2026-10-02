#include "global.h"
#include "ram_map.h"
#include "battle.h"

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

