#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08070188
/* match-compiler: old_agbcc */
// Resize a battle-object batch to count nodes: grow it in place from the free
// list (new nodes inherit the batch's key), allocate it fresh if it is empty,
// or release and reallocate it when shrinking. Returns the batch head.
struct Unk6FDB4 *sub_08070188(struct Unk700CCHdr *hdr, u16 count, u16 key)
{
    struct Unk6FDB4 *head;
    struct Unk6FDB4 *tail;
    struct Unk6FDB4 *cur;
    struct Unk6FDB4 *prev;
    u32 avail;

    if (hdr->unk08 == count)
        return hdr->unk00;
    if (hdr->unk08 < count)
    {
        if (hdr->unk08 != 0)
        {
            count -= hdr->unk08;
            avail = gData_030040B4;
            if (avail < count)
            {
                sub_08067A9C((void *)0x083D2288);
                return NULL;
            }
            head = gData_030040AC;
            cur = head;
            tail = hdr->unk04;
            prev = head;
            key = hdr->unk00->unk22;
            gData_030040B4 = avail - count;
            hdr->unk08 += count;
            head->unk22 = key;
            while (--count != 0)
            {
                cur = cur->unk04;
                cur->unk22 = key;
                cur->unk00 = prev;
                prev = cur;
            }
            gData_030040AC = cur->unk04;
            if (tail->unk04 != NULL)
                tail->unk04->unk00 = cur;
            cur->unk04 = tail->unk04;
            tail->unk04 = head;
            head->unk00 = tail;
            hdr->unk04 = cur;
            sub_0806F8C4((struct Unk6F8C4 *)gData_030040A4);
            return hdr->unk00;
        }
        BtlObjPoolAllocChain(hdr, count, key);
        return hdr->unk00;
    }
    sub_08067A9C((void *)0x083D22A4);
    sub_080700CC(hdr);
    return BtlObjPoolAllocChain(hdr, count, key);
}

