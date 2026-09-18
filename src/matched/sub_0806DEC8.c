#include "global.h"

// @ 0x0806dec8
u8 *sub_0806DEC8(struct UnkDEC8 *a, s32 index)
{
    u8 *node;
    s32 i;

    node = a->unk08;
    for (i = 0; i < a->unk00->unk04; i++)
    {
        if (i == index)
            return node;
        node += *(u32 *)(node + 4);
    }
    return 0;
}

