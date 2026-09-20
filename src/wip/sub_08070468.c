#define sub_08070468 sub_08070468_old_proto
#include "global.h"
#undef sub_08070468

void sub_08070468(struct Unk6FDB4 *arg, u16 key)
{
    register struct Unk6FDB4 *node;
    register u16 new_key;
    register struct Unk6FDB4 **head;
    register struct Unk6FDB4 **search_head;
    register struct Unk6FDB4 *found;
    struct Unk6FDB4 *previous;
    struct Unk6FDB4 *next;

    node = arg;
    new_key = key;
    if (node->unk22 == new_key)
        return;
    previous = node->unk00;
    if (previous != 0)
    {
        next = node->unk04;
        previous->unk04 = next;
        head = (struct Unk6FDB4 **)(void *)&gUnk_030040A4;
    }
    else
    {
        head = (struct Unk6FDB4 **)(void *)&gUnk_030040A4;
        next = node->unk04;
        *head = next;
    }
    if (next != 0)
        next->unk00 = previous;
    node->unk22 = new_key;
    search_head = head;
    found = sub_0806FDB4(*search_head, new_key);
    if (found == 0)
    {
        if (*search_head != 0)
            (*search_head)->unk00 = node;
        node->unk04 = *head;
        node->unk00 = found;
        *head = node;
    }
    else
    {
        if (found->unk04 != 0)
            found->unk04->unk00 = node;
        node->unk04 = found->unk04;
        node->unk00 = found;
        found->unk04 = node;
    }
}
