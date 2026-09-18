#include "global.h"

// @ 0x080720f0
void *sub_080720F0(u32 i, u32 b)
{
    struct Unk40D4 *p;

    p = *(struct Unk40D4 **)gUnk_030040D4;
    if (i < p->unk04)
        return sub_08071EE4(p->unk0C[i], b);
    return (void *)p->unk04;
}

