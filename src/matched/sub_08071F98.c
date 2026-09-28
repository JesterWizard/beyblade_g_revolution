#include "global.h"

// @ 0x08071f98
void SoundPause(s32 a)
{
    struct Unk71E84 *p;

    p = SoundFindChannel(a);
    if (p != 0)
        p->unk16 = 2;
}

