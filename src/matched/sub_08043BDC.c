#include "global.h"

// @ 0x08043bdc
void *BtlFindUnk16E4(void)
{
    struct Unk16E0 *p;

    p = gMainWorkPtr->unk16E4;
    if (p == 0)
        return 0;
    while (p->unk00 != 0)
    {
        if (sub_08073440(p->unk00, gMainWorkPtr->unk16C8) == 0)
            return (void *)p->unk04;
        p++;
    }
    return 0;
}

