#include "global.h"

// @ 0x08071fac

void SoundResume(s32 a)
{
    struct Unk71E84 *p;

    p = SoundFindChannel(a);
    if (p != 0 && p->unk16 == 2)
        p->unk16 = 1;
}

