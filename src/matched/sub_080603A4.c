#include "global.h"

// @ 0x080603a4
void sub_080603A4(u16 a)
{
    s32 v;

    v = gMainWorkPtr->unk177C;
    if (v != -1)
        sub_08071FC8(v, a);
    gMainWorkPtr->unk1819 = a;
}

