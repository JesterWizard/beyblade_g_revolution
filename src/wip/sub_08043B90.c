#include "global.h"

/* 54/76 same size. Walks MainWork.unk16E0 (8-byte records) until
 * sub_08073440(node->unk00, unk16C8) returns 0, then returns node->unk04.
 * Null list returns -1. The loaded word stays in r2; retail keeps it in r0
 * so the call does not need `adds r0, r2, #0`. */
s32 sub_08043B90(void)
{
    struct Unk16E0 *node = gMainWorkPtr->unk16E0;
    void *v;

    if (node == 0)
        return -1;
    while ((v = node->unk00) != 0)
    {
        if (sub_08073440(v, gMainWorkPtr->unk16C8) == 0)
            return node->unk04;
        node++;
    }
    return (s32)v;
}
