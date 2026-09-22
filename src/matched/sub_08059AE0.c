#include "global.h"

// @ 0x08059ae0
void *sub_08059AE0(struct Unk59AE0Src *src)
{
    struct Unk59AE0Node *node = *(struct Unk59AE0Node **)gUnk_03000730;
    s32 i = 0;

    if (node == 0)
        return 0;

    while (1)
    {
        if (node->unk00 == 0)
        {
            node->unk00 = src->unk00;
            node->unk04 = src->unk04;
            node->unk08 = src->unk08;
            node->unk18 = src->unk10;
            node->unk1C = src->unk14;
            node->unk20 = src->unk18;
            node->unk24 = src->unk1C;
            node->unk28 = (struct Unk59AE0Src *)src->unk20;
            node->unk38 = 0;
            node->unk34 = 0;
            node->unk2C = 0;
            node->unk30 = 0;
            node->unk14 = 1;

            if (src->unk0C != 0)
            {
                node->unk0C = (u32)BtlObjAlloc(src->unk0C);
                node->unk10 = *(u32 *)node->unk0C;
            }

            return node;
        }

        node = (struct Unk59AE0Node *)((u8 *)node + 0x3C);
        i++;
        if (i > 0x13)
            break;
    }

    return 0;
}

