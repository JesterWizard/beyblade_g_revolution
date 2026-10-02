#include "global.h"

// @ 0x080628b4
u32 RandRange(u32 a)
{
    u32 seed;

    seed = gMainWorkPtr->unk1800 * 0x36F1ACE3;
    gMainWorkPtr->unk1800 = seed;
    return sub_08074264((seed * 0x9FBF1) >> 16, a);
}

