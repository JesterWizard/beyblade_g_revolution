#include "global.h"

// @ 0x080603a4
void BgmSetVolume(u16 a)
{
    s32 v;

    v = gMainWorkPtr->unk177C;
    if (v != -1)
        SoundSetVolume(v, a);
    gMainWorkPtr->unk1819 = a;
}

