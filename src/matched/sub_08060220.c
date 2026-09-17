#include "global.h"

// @ 0x08060220
void sub_08060220(u32 idx)
{
    s32 v;

    v = gMainWorkPtr->unk1710[idx];
    if (v != -1)
    {
        sub_08071F84(v);
        gMainWorkPtr->unk1710[idx] = -1;
    }
}

