#include "global.h"

// @ 0x0806013c
void BgmStop(void)
{
    s32 v;

    v = gMainWorkPtr->bgmHandle;
    if (v != -1)
    {
        SoundStop(v);
        gMainWorkPtr->bgmHandle = -1;
        gMainWorkPtr->bgmTrack = -1;
    }
}

