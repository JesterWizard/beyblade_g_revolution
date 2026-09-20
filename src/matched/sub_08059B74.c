#include "global.h"

// @ 0x08059b74
void sub_08059B74(void)
{
    struct Unk59AE0Node *node = *(struct Unk59AE0Node **)gUnk_03000730;
    s32 i;
    u32 arg;

    if (node == 0)
        return;

    for (i = 0x13; i >= 0; i--)
    {
        switch (node->unk14)
        {
        case 1:
            if (node->unk00 != 0)
            {
                arg = node->unk00;
            }
            else
            {
                node->unk14 = 2;
                arg = node->unk04;
            }
            if (_08073C44(node, (void *)arg))
                node->unk14++;
            break;

        case 2:
            arg = node->unk04;
            if (arg == 0)
                break;
            if (_08073C44(node, (void *)arg))
                node->unk14++;
            break;

        case 3:
            sub_08059BD8((void *)node->unk04, 1);
            break;

        default:
            break;
        }

        node = (struct Unk59AE0Node *)((u8 *)node + 0x3C);
    }
}

