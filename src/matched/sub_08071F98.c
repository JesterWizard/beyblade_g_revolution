#include "global.h"

// @ 0x08071f98
void SoundPause(s32 a)
{
    struct SoundChannel *p;

    p = SoundFindChannel(a);
    if (p != 0)
        p->state = 2;
}

