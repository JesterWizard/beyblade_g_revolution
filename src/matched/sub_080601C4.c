#include "global.h"

// @ 0x080601c4
void sub_080601C4(u32 a, u32 b)
{
    if (gMainWorkPtr->unk1710[a] != -1)
        sub_08071F84(gMainWorkPtr->unk1710[a]);

    gMainWorkPtr->unk1710[a] = (s32)sub_080720F0(a, b);
    sub_08071FC8(gMainWorkPtr->unk1710[a], gMainWorkPtr->unk181A);
}

