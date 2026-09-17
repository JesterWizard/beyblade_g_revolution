#include "global.h"

// @ 0x0806013c
void sub_0806013C(void)
{
    s32 v;

    v = gMainWorkPtr->unk177C;
    if (v != -1)
    {
        sub_08071F84(v);
        gMainWorkPtr->unk177C = -1;
        gMainWorkPtr->unk1780 = -1;
    }
}

