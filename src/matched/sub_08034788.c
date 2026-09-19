#include "global.h"

// @ 0x08034788
void sub_08034788(void *a, u32 b, u32 *c, u32 *d)
{
    struct Unk705DC **pa = a;
    struct Unk705DC **pb = (struct Unk705DC **)b;

    if (c != 0 && d != 0)
    {
        *c = (s32)((*pa)->unk0C + (*pb)->unk0C) >> 1;
        *d = (s32)((*pa)->unk10 + (*pb)->unk10) >> 1;
    }
}

