#include "global.h"

// @ 0x08068014

void *AnimRecAt(struct Unk68014 **slot, u32 i)
{
    struct Unk68014Rec *p;

    p = (*slot)->unk20;
    return &p[i];
}

