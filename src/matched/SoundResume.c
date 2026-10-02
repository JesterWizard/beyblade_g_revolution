#include "global.h"

// @ 0x08071fac

void SoundResume(s32 a)
{
    struct SoundChannel *p;

    p = SoundFindChannel(a);
    if (p != 0 && p->state == 2)
        p->state = 1;
}

