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

