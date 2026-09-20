#include "global.h"

// @ 0x08043B90
s32 sub_08043B90(void)
{
    struct Unk16E0 *p;

    p = gMainWorkPtr->unk16E0;
    if (p == 0)
        return -1;
    while (p->unk00 != 0)
    {
        if (sub_08073440(p->unk00, gMainWorkPtr->unk16C8) == 0)
            return p->unk04;
        p++;
    }
    return (s32)p->unk00;
}
