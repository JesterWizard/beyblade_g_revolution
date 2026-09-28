#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806121c
/* match-compiler: old_agbcc */
// Set up the gData_03000798 window: clear it, record the source and count,
// lay out its tile block (sub_08061628) and finish with sub_08061308.
void TextWindowOpen(struct Unk617C4 *src, u32 b, u16 count, u16 c, u16 d, u16 e, u16 f, u16 g)
{
    u16 attr;
    struct Unk0798 *st;

    attr = g << 12;
    ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, gData_03000798, 0xAC);
    st = gData_03000798;
    st->unk88 = src;
    st->unk8C = b;
    st->unk94 = count;
    st->unk96 = attr;
    st->unkA0 = src->unk04;
    st->unkA2 = src->unk05;
    st->unk90 = 0;
    st->unk92 = 0;
    st->unk9C = st->unkA0 >> 2;
    st->unkA4 = 0;
    st->unkA6 = 0;
    sub_08068BD4((struct Unk68E54 *)st, 3, count, 0);
    TextWindowLayout((u8)e, (u8)f, (u8)c, (u8)d, (u16)(count - 1));
    sub_08061308();
}

