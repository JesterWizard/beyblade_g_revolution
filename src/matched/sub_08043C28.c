#include "global.h"

// @ 0x08043c28
void sub_08043C28(void)
{
    struct Unk05F0 *p;

    p = (struct Unk05F0 *)gUnk_030005F0;
    if (p->unk00 != 0)
    {
        BtlObjFree(p->unk00);
        p->unk00 = 0;
    }
    if (p->unk04 != 0)
    {
        BtlObjFree(p->unk04);
        p->unk04 = 0;
    }
    if (p->unk08 != 0)
    {
        BtlObjFree(p->unk08);
        p->unk08 = 0;
    }
    if (p->unk0C != 0)
    {
        BtlObjFree(p->unk0C);
        p->unk0C = 0;
    }
}

