#include "global.h"

// @ 0x0802b930
// The beyblade roster lookup: 62 records of 0x1C bytes at ROM 0x08075AB8. Scans
// for the record whose `id` (s16 +0x04) equals the argument and returns its
// `profile` (s32 +0x00), or -1. The address stays a literal: as a data symbol
// agbcc folds the pool load differently and the bytes stop matching (see the
// note at the top of asm/data_symbols.s).
s32 BeybladeGetProfile(s32 a)
{
    s32 i;
    struct BeybladeDef *p;

    i = 0;
    p = (struct BeybladeDef *)0x08075AB8;
    for (; i <= 0x3D; p++, i++)
    {
        if (p->id == a)
            return p->profile;
    }
    return -1;
}
