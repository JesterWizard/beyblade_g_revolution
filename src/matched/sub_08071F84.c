#include "global.h"

// @ 0x08071f84
void SoundStop(s32 a)
{
    struct Unk71E84 *p;

    p = SoundFindChannel(a);
    if (p != 0)
        p->unk16 = 0;
}

