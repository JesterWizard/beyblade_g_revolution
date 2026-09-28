#include "global.h"

// @ 0x080720f0
void *SoundPlayIndexed(u32 i, u32 b)
{
    struct Unk40D4 *p;

    p = *(struct Unk40D4 **)gUnk_030040D4;
    if (i < p->unk04)
        return SoundPlay(p->unk0C[i], b);
    return (void *)p->unk04;
}

