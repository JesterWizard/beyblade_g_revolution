#include "global.h"

// @ 0x08068014

void *AnimRecAt(struct AnimData **slot, u32 i)
{
    struct AnimRecord *p;

    p = (*slot)->unk20;
    return &p[i];
}

