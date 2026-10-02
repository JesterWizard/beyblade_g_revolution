#include "global.h"

// @ 0x0803e258
struct Unk8D0 *Unk8D0FindActiveById(s16 a)
{
    s32 i;

    for (i = 0; i <= 0x52; i++)
    {
        if (gMainWorkPtr->unk08D0[i].unk1C == a && gMainWorkPtr->unk087C[i] == 1)
            return &gMainWorkPtr->unk08D0[i];
    }

    return 0;
}

