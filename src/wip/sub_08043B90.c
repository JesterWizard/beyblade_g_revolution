#include "global.h"

// @ 0x08043b90
s32 sub_08043B90(void)
{
    void *r0;
    struct Unk16E0 *p;

    p = gMainWorkPtr->unk16E0;
    if (p == 0)
        return -1;
    while ((r0 = p->unk00) != 0)
    {
        if (sub_08073440(p->unk00, gMainWorkPtr->unk16C8) == 0)
            return p->unk04;
        p++;
    }
    return (s32)r0;
}

