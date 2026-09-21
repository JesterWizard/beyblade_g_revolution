#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806fefc
/* match-compiler: old_agbcc */
#include "ram_map.h"

// @ 0x0806fefc
// Pop the head node off the battle-object list and push it onto the tail list.
// gData_030040A8/gData_030040B8 symbols (not raw literals) stop agbcc folding
// 0x030040B8 into 0x030040A8+0x10.
struct BtlObjNode *sub_0806FEFC(void)
{
    struct BtlObjNode *n = *(struct BtlObjNode **)gData_030040A8;
    struct BtlObjNode *t;

    if (n != 0)
    {
        *(struct BtlObjNode **)gData_030040A8 = n->prev;
        t = *(struct BtlObjNode **)gData_030040B8;
        if (t != 0)
            t->next = n;
        n->prev = *(struct BtlObjNode **)gData_030040B8;
        n->next = 0;
        *(struct BtlObjNode **)gData_030040B8 = n;
    }
    return n;
}

