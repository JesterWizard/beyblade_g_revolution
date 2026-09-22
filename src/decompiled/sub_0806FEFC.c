#include "global.h"

// @ 0x0806fefc
#include "global.h"

/* match-flags: -fprologue-bugfix */

struct BtlObjNode *sub_0806FEFC(void)
{
    u32 r2;
    struct BtlObjNode *r1;
    struct BtlObjNode *r0;

    r2 = (u32)gBtlObjListHeadLoc;
r1 = *(struct BtlObjNode **)r2;
    if (r1 != 0)
    {
        r0 = r1->prev;
        *(struct BtlObjNode **)r2 = r0;
        r2 = (u32)gBtlObjListTailLoc;
r0 = *(struct BtlObjNode **)r2;
        if (r0 != 0)
            r0->next = r1;
        r0 = *(struct BtlObjNode **)r2;
        r1->prev = r0;
        r0 = 0;
        r1->next = r0;
        *(struct BtlObjNode **)r2 = r1;
    }
    r0 = r1;
    return r0;
}

