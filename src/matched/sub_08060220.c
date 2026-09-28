#include "global.h"

// @ 0x08060220
void SfxStopSlot(u32 idx)
{
    s32 v;

    v = gMainWorkPtr->unk1710[idx];
    if (v != -1)
    {
        SoundStop(v);
        gMainWorkPtr->unk1710[idx] = -1;
    }
}

