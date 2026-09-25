#include "global.h"
#include "ram_map.h"

/* match-compiler: old_agbcc */
// @ 0x0807000c
// Allocate `count` linked battle-object pool nodes with the given key.
struct Unk6FDB4 *BtlObjPoolAllocChain(struct Unk700CCHdr *hdr, u32 count_arg, u32 key_arg)
{
    u16 count;
    u16 key;
    struct Unk6FDB4 *head;
    struct Unk6FDB4 *cur;
    struct Unk6FDB4 *prev;
    struct Unk6FDB4 *insert_after;
    u32 tmp[1];

    count = (u16)count_arg;
    key = (u16)key_arg;
    if (gUnk_030040B4 < count)
    {
        DebugPrint((void *)0x083D2244, gUnk_030040B4, count);
        return 0;
    }
    gUnk_030040B4 -= count;
    head = gUnk_030040AC;
    cur = head;
    tmp[0] = 0x030040A4;
    insert_after = sub_0806FDB4(*(struct Unk6FDB4 **)tmp[0], key);
    prev = head;
    hdr->unk08 = count;
    hdr->unk00 = head;
    head->unk22 = key;
    while (1)
    {
        count--;
        if (count == 0)
            break;
        cur = cur->unk04;
        cur->unk22 = key;
        cur->unk00 = prev;
        prev = cur;
    }
    hdr->unk04 = cur;
    gUnk_030040AC = cur->unk04;
    if (insert_after == 0)
    {
        tmp[0] = 0x030040A4;
        if (*(struct Unk6FDB4 **)tmp[0] != 0)
            (*(struct Unk6FDB4 **)tmp[0])->unk00 = cur;
        cur->unk04 = *(struct Unk6FDB4 **)tmp[0];
        head->unk00 = 0;
        *(struct Unk6FDB4 **)tmp[0] = head;
        sub_0806F8C4((struct Unk6F8C4 *)*(struct Unk6FDB4 **)tmp[0]);
    }
    else
    {
        if (insert_after->unk04 != 0)
            insert_after->unk04->unk00 = cur;
        cur->unk04 = insert_after->unk04;
        head->unk00 = insert_after;
        insert_after->unk04 = head;
        tmp[0] = 0x030040A4;
        sub_0806F8C4((struct Unk6F8C4 *)*(struct Unk6FDB4 **)tmp[0]);
    }
    return head;
}
