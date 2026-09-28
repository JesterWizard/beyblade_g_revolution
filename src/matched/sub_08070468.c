#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08070468
/* Move a node to its sorted position in the gData_030040A4 list after its key changes. */
void BtlObjListResort(struct Unk6FDB4 *node, u16 key)
{
    struct Unk6FDB4 *found;

    if (node->unk22 == key)
        return;
    if (node->unk00 != NULL)
        node->unk00->unk04 = node->unk04;
    else
        gData_030040A4 = node->unk04;
    if (node->unk04 != NULL)
        node->unk04->unk00 = node->unk00;
    node->unk22 = key;
    found = BtlObjListFindInsertPoint(gData_030040A4, key);
    if (found == NULL)
    {
        if (gData_030040A4 != NULL)
            gData_030040A4->unk00 = node;
        node->unk04 = gData_030040A4;
        node->unk00 = found;
        gData_030040A4 = node;
    }
    else
    {
        if (found->unk04 != NULL)
            found->unk04->unk00 = node;
        node->unk04 = found->unk04;
        node->unk00 = found;
        found->unk04 = node;
    }
}

