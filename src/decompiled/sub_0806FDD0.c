/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
void *BtlObjPoolAlloc(u16 key_arg)
{
    u16 key;
    struct Unk6FDB4 *node;
    struct Unk6FDB4 **head_loc;
    struct Unk6FDB4 **free_loc;
    struct Unk6FDB4 *previous;

    key = key_arg;
    free_loc = (struct Unk6FDB4 **)0x030040AC;
    node = *free_loc;
    if (node != 0)
    {
        head_loc = (struct Unk6FDB4 **)0x030040A4;
        previous = sub_0806FDB4(*head_loc, key);
        node->unk22 = key;
        *free_loc = node->unk04;
        if (previous == 0)
        {
            if (*head_loc != 0)
                (*head_loc)->unk00 = node;
            node->unk04 = *head_loc;
            node->unk00 = 0;
            *head_loc = node;
        }
        else
        {
            if (previous->unk04 != 0)
                previous->unk04->unk00 = node;
            node->unk04 = previous->unk04;
            node->unk00 = previous;
            previous->unk04 = node;
        }
        gUnk_030040B4--;
    }
    else
        DebugMessage((void *)0x083D2230);
    sub_0806F8C4((struct Unk6F8C4 *)gUnk_030040A4);
    return node;
}
