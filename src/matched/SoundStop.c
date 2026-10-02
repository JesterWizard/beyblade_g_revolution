#include "global.h"

// @ 0x08071f84
void SoundStop(s32 a)
{
    struct SoundChannel *p;

    p = SoundFindChannel(a);
    if (p != 0)
        p->state = 0;
}

