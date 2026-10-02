#include "global.h"

// @ 0x08034360
void sub_08034360(struct Unk33F30 *a)
{
    if (a->unk33 != 0)
    {
        a->unk33 = 0;
        GlyphTextFree(&a->unk34);
    }
}

