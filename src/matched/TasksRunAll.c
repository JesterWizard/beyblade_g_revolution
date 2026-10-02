#include "global.h"

// @ 0x08059b74
void TasksRunAll(void)
{
    struct Task *node = *(struct Task **)gUnk_03000730;
    s32 i;
    u32 arg;

    if (node == 0)
        return;

    for (i = 0x13; i >= 0; i--)
    {
        switch (node->stage)
        {
        case 1:
            if (node->initFn != 0)
            {
                arg = node->initFn;
            }
            else
            {
                node->stage = 2;
                arg = node->updateFn;
            }
            if (_08073C44(node, (void *)arg))
                node->stage++;
            break;

        case 2:
            arg = node->updateFn;
            if (arg == 0)
                break;
            if (_08073C44(node, (void *)arg))
                node->stage++;
            break;

        case 3:
            TaskDestroyByUpdateFn((void *)node->updateFn, 1);
            break;

        default:
            break;
        }

        node = (struct Task *)((u8 *)node + 0x3C);
    }
}

