#include "global.h"

// @ 0x0806ff28
#include "global.h"

/* match-flags: -fprologue-bugfix */

void sub_0806FF28(struct BtlObj *a)
{
    register struct BtlObj *r3;
    register u32 r0;
    register struct BtlObjNode *r2;
    register struct BtlObjNode *r1;
    register u32 loc;

    r3 = a;
    r0 = r3->unk19;
    if (r0 == 0)
    {
        r2 = r3->next;
        r1 = r3->prev;
        if (r2 != 0)
            r2->prev = r1;
        else
        {
            r0 = (u32)gBtlObjListTailLoc;
*(struct BtlObjNode **)r0 = r1;
        }
        if (r1 != 0)
            r1->next = r2;
        loc = (u32)gBtlObjListHeadLoc;
r0 = *(u32 *)loc;
        r3->prev = (struct BtlObjNode *)r0;
        *(struct BtlObj **)loc = r3;
    }
}

