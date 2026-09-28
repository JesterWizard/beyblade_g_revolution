#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0807000c
// Allocate `count` linked battle-object pool nodes tagged with `key` from the
// free list and splice the chain into the active list after the key's run.
struct Unk6FDB4 *BtlObjPoolAllocChain(struct SpriteChain *hdr, u16 count, u16 key)
{
    struct Unk6FDB4 *head;
    struct Unk6FDB4 *cur;
    struct Unk6FDB4 *prev;
    struct Unk6FDB4 *after;

    if (gData_030040B4 < count)
    {
        DebugPrint((void *)0x083D2244, gData_030040B4, count);
        return 0;
    }
    gData_030040B4 -= count;
    head = gData_030040AC;
    cur = head;
    after = BtlObjListFindInsertPoint(gData_030040A4, key);
    prev = head;
    hdr->count = count;
    hdr->head = head;
    head->unk22 = key;
    while (--count != 0)
    {
        cur = cur->unk04;
        cur->unk22 = key;
        cur->unk00 = prev;
        prev = cur;
    }
    hdr->tail = cur;
    gData_030040AC = cur->unk04;
    if (after == 0)
    {
        if (gData_030040A4 != 0)
            gData_030040A4->unk00 = cur;
        cur->unk04 = gData_030040A4;
        head->unk00 = after;
        gData_030040A4 = head;
    }
    else
    {
        if (after->unk04 != 0)
            after->unk04->unk00 = cur;
        cur->unk04 = after->unk04;
        head->unk00 = after;
        after->unk04 = head;
    }
    LinkedListValidate((struct Unk6F8C4 *)gData_030040A4);
    return head;
}

