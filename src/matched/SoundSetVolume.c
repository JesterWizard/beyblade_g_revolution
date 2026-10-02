#include "global.h"

// @ 0x08071fc8
void SoundSetVolume(s32 a, u32 b)
{
    struct SoundChannel *p;

    p = SoundFindChannel(a);
    if (p != 0)
    {
        if (b > 0x100)
            b = 0x100;
        p->volume = b;
    }
}

