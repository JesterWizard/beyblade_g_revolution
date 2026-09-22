#include "global.h"

void *BtlObjPoolAlloc(u16 key_arg)
{
    u16 key;
    struct Unk6FDB4 *node;
    struct Unk6FDB4 **head_loc;
    struct Unk6FDB4 **free_loc;
    struct Unk6FDB4 *previous;
    struct Unk6FDB4 *next;
    u32 count;

    key = key_arg;
    free_loc = (struct Unk6FDB4 **)0x030040AC;
    node = *free_loc;
    if (node == 0)
    {
        DebugMessage((void *)0x083D2230);
        goto finish;
    }
    head_loc = (struct Unk6FDB4 **)0x030040A4;
    previous = sub_0806FDB4(*head_loc, key);
    node->unk22 = key;
    next = node->unk04;
    *free_loc = next;
    if (previous == 0)
    {
        next = *head_loc;
        if (next != 0)
            next->unk00 = node;
        node->unk04 = next;
        node->unk00 = 0;
        *head_loc = node;
    }
    else
    {
        next = previous->unk04;
        if (next != 0)
            next->unk00 = node;
        node->unk04 = next;
        node->unk00 = previous;
        previous->unk04 = node;
    }
    count = gUnk_030040B4;
    count--;
    gUnk_030040B4 = count;
finish:
    sub_0806F8C4((struct Unk6F8C4 *)gUnk_030040A4);
    return node;
}
