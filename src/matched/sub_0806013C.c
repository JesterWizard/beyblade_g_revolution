#include "global.h"

// @ 0x0806013c
void BgmStop(void)
{
    s32 v;

    v = gMainWorkPtr->unk177C;
    if (v != -1)
    {
        SoundStop(v);
        gMainWorkPtr->unk177C = -1;
        gMainWorkPtr->unk1780 = -1;
    }
}

