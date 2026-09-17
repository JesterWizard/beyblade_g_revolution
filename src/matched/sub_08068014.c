#include "global.h"

// @ 0x08068014

void *sub_08068014(struct Unk68014 **slot, u32 i)
{
    struct Unk68014Rec *p;

    p = (*slot)->unk20;
    return &p[i];
}

