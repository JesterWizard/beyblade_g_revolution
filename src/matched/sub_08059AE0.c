#include "global.h"

// @ 0x08059ae0
void *TaskCreate(struct TaskTemplate *src)
{
    struct Task *node = *(struct Task **)gUnk_03000730;
    s32 i = 0;

    if (node == 0)
        return 0;

    while (1)
    {
        if (node->initFn == 0)
        {
            node->initFn = src->initFn;
            node->updateFn = src->updateFn;
            node->destroyFn = src->destroyFn;
            node->unk18 = src->unk10;
            node->unk1C = src->unk14;
            node->unk20 = src->unk18;
            node->unk24 = src->unk1C;
            node->unk28 = (struct TaskTemplate *)src->unk20;
            node->unk38 = 0;
            node->unk34 = 0;
            node->unk2C = 0;
            node->unk30 = 0;
            node->stage = 1;

            if (src->unk0C != 0)
            {
                node->heap = (u32)HeapAlloc(src->unk0C);
                node->unk10 = *(u32 *)node->heap;
            }

            return node;
        }

        node = (struct Task *)((u8 *)node + 0x3C);
        i++;
        if (i > 0x13)
            break;
    }

    return 0;
}

