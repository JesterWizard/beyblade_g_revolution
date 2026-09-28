#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080700cc
// Release a pending battle-object batch: return its nodes to the free list,
// unlink the run from the active list and clear the batch header.
void BtlObjPoolReleaseChain(void *a)
{
    struct Unk700CCHdr *batch;
    struct Unk700CCNode *node;
    struct Unk700CCNode *head;
    struct Unk700CCNode *tail;
    struct Unk700CCNode *prev;
    struct Unk700CCNode *next;
    u32 count;
    u32 i;

    batch = a;
    count = batch->unk08;
    if (count == 0)
        return;
    head = (struct Unk700CCNode *)batch->unk00;
    tail = (struct Unk700CCNode *)batch->unk04;
    prev = head->unk00;
    next = tail->unk04;
    gData_030040B4 += count;
    node = head;
    i = count;
    while (i-- != 0)
    {
        if (node->unk30 != 0)
        {
            BtlObjListMoveToHead(node->unk30);
            node->unk30 = 0;
        }
        if (node->unk24 >= 0)
            VramSpanFree(node->unk24, 1 << (node->unk16 - 5));
        node->unk24 = -1;
        node = node->unk04;
    }

    if (prev != 0)
        prev->unk04 = next;
    else
        gData_030040A4 = (struct Unk6FDB4 *)next;
    if (next != 0)
        next->unk00 = prev;
    tail->unk04 = (struct Unk700CCNode *)gData_030040AC;
    gData_030040AC = (struct Unk6FDB4 *)head;
    batch->unk08 = 0;
    batch->unk00 = 0;
    batch->unk04 = 0;
    sub_0806F8C4((struct Unk6F8C4 *)gData_030040A4);
}

