#include "global.h"

// @ 0x080601c4
void SfxPlayInSlot(u32 a, u32 b)
{
    if (gMainWorkPtr->unk1710[a] != -1)
        SoundStop(gMainWorkPtr->unk1710[a]);

    gMainWorkPtr->unk1710[a] = (s32)SoundPlayIndexed(a, b);
    SoundSetVolume(gMainWorkPtr->unk1710[a], gMainWorkPtr->unk181A);
}

