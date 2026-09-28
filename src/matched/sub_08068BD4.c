#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068bd4
/* match-compiler: old_agbcc */
// Initialises an affine BG layer: resets the scroll/scale state, points it at
// its visible-rect slot, reserves char blocks (gData_03000108 grows upwards)
// and screen blocks (gData_030001A8 grows downwards) for the tile data,
// clears that VRAM and writes the BGxCNT value.
void AffineBgInit(struct Unk68E54 *st, u8 bg, u16 tiles, u16 cnt)
{
    u32 size;
    struct Unk688C8Rect *rect;
    u32 blocks;
    u32 n;
    u32 m;
    u16 *reg;
    void *vram;

    st->unk68 = 0;
    st->unk64 = 0;
    size = OamShapeToSize((struct Unk691E4 *)st, cnt, 0);
    rect = &gData_03000008[bg];
    st->unk08 = rect;
    rect->unk10 = 0;
    rect->unk14 = 0;
    rect->unk00 = 0;
    rect->unk08 = (1 << st->unk5F) - 1;
    rect->unk04 = 0;
    rect->unk0C = (1 << st->unk60) - 1;
    st->unk00 = 0x20;
    st->unk04 = 0x20;
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
    st->unk7C = 0;
    st->unk80 = -1;
    st->unk84 = 0;
    st->unk6C = 0;
    if (cnt & 0x80)
        st->unk74 = tiles << 6;
    else
        st->unk74 = tiles << 5;
    st->unk70 = 0;
    st->unk78 = 0;
    blocks = (st->unk74 - 1) >> 14;
    st->unk5D = gData_03000108;
    if (st->unk74 != 0)
        gData_03000108 += 1 + blocks;
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
    vram = (void *)(st->unk5C * 0x800 + 0x06000000);
    ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, vram, size);
    reg = BgGetCntReg(bg);
    *reg = (st->unk5C << 8) | cnt | (st->unk5D << 2);
}

