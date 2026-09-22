#include "global.h"

// @ 0x08066bc4
void sub_08066BC4(struct Unk66BC4 *a, u32 i)
{
    void **t;

    i <<= 16;
    t = *a->unk230;
    TextEntrySetPaletteBank(t[i >> 16], 0x0E);
    a->unk310 = 8;
}

