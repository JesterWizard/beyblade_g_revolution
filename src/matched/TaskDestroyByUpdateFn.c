#include "global.h"

// @ 0x08059bd8
void TaskDestroyByUpdateFn(void *a, u32 b)
{
    struct Task *node = *(struct Task **)gUnk_03000730;
    s32 i = 0;
    struct TaskTemplate *src;

    if (node == 0)
        return;

    while (1)
    {
        if (node->updateFn == (u32)a)
        {
            if (node->destroyFn != 0)
                _08073C44(node, (void *)node->destroyFn);

            node->initFn = 0;
            node->updateFn = 0;
            node->destroyFn = 0;
            node->stage = 0;

            if (node->heap != 0)
            {
                HeapFree((void *)node->heap);
                node->heap = 0;
            }

            if (b != 0)
            {
                src = (struct TaskTemplate *)node->unk28;
                if (src != 0)
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
                        node->heap = (u32)HeapAlloc(src->unk0C);

                    return;
                }
            }

            node->unk28 = 0;
            return;
        }

        node = (struct Task *)((u8 *)node + 0x3C);
        i++;
        if (i > 0x13)
            break;
    }
}

