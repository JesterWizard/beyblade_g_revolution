#include "global.h"

// @ 0x0803484c
void sub_0803484C(struct Unk3484C *a)
{
    if (a->unk00 != 0)
        TextEntrySetPaletteBank(*(void **)a->unk00, a->unk2D0);
}

