#include "global.h"

// @ 0x08061610
void TextSetPaletteBank(u16 a)
{
    s32 v;
    struct TextWindow *p;

    v = a;
    p = gUnk_03000798;
    v &= 15;
    v <<= 12;
    p->baseTile = v;
}

