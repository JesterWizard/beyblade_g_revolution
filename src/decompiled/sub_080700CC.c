#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080700cc
void sub_080700CC(void *a)
{
    struct Unk700CCHdr *batch;
    struct Unk700CCNode *node;
    struct Unk700CCNode *head;
    struct Unk700CCNode *tail;
    struct Unk700CCNode *headLink;
    struct Unk700CCNode *tailLink;
    u32 count;
    s32 minusOne;

    batch = a;
    count = batch->unk08;
    if (count == 0)
        return;
    head = (struct Unk700CCNode *)batch->unk00;
    tail = (struct Unk700CCNode *)batch->unk04;
    headLink = head->unk00;
    tailLink = tail->unk04;
    gUnk_030040B4 += count;
    node = head;
    count--;
    minusOne = -1;
    while (count != minusOne)
    {
        if (node->unk30 != 0)
        {
            BtlObjListMoveToHead(node->unk30);
            node->unk30 = 0;
        }
        if (node->unk24 >= 0)
            sub_0806FBF8(node->unk24, 1 << (node->unk16 - 5));
        node->unk24 = minusOne;
        node = node->unk04;
        count--;
    }
    if (headLink != 0)
        headLink->unk04 = tailLink;
    else
        gUnk_030040A4 = (struct Unk6FDB4 *)tailLink;
    if (tailLink != 0)
        tailLink->unk00 = headLink;
    tail->unk04 = (struct Unk700CCNode *)gUnk_030040AC;
    gUnk_030040AC = (struct Unk6FDB4 *)head;
    batch->unk08 = 0;
    batch->unk00 = 0;
    batch->unk04 = 0;
    sub_0806F8C4((struct Unk6F8C4 *)gUnk_030040A4);
}
