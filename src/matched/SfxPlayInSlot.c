#include "global.h"

// @ 0x080601c4
void SfxPlayInSlot(u32 a, u32 b)
{
    if (gMainWorkPtr->sfxHandles[a] != -1)
        SoundStop(gMainWorkPtr->sfxHandles[a]);

    gMainWorkPtr->sfxHandles[a] = (s32)SoundPlayIndexed(a, b);
    SoundSetVolume(gMainWorkPtr->sfxHandles[a], gMainWorkPtr->sfxVolume);
}

