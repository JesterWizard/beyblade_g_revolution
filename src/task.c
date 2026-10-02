#include "global.h"

/* fn: sub_080447B4 */
// @ 0x080447b4
void TaskCreateList(void **a)
{
    void *p;

    while (1)
    {
        p = *a;
        a++;
        if (p == 0)
            break;
        TaskCreate(p);
    }
}

/* fn: sub_08059AE0 */
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

/* fn: sub_08059B74 */
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

/* fn: sub_08059BD8 */
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

/* fn: sub_08059C6C */
// @ 0x08059c6c
void TasksDestroyAll(void)
{
    struct Unk59C6C *p;
    s32 n;

    p = *(struct Unk59C6C **)gUnk_03000730;
    if (p == 0)
        return;
    n = 0x13;
    do
    {
        if (p->unk04 != 0)
            TaskDestroyByUpdateFn(p->unk04, 0);
        p++;
        n--;
    } while (n >= 0);
}

/* fn: sub_08059C98 */
// @ 0x08059c98
void *TaskCreateWithOwner(struct Unk59C98Src *src, struct Unk59C98Owner *owner, void *a2, void *a3)
{
    struct Unk59C6C *p;
    s32 i;
    void *q;
    void *tmp;

    p = *(struct Unk59C6C **)gUnk_03000730;
    i = 0;
    if (p == 0)
        return 0;
    do
    {
        tmp = p->unk00;
        if (tmp == 0)
        {
            p->unk00 = src->unk00;
            p->unk04 = src->unk04;
            p->unk08 = src->unk08;
            p->unk18 = src->unk10;
            p->unk1C = src->unk14;
            p->unk20 = src->unk18;
            p->unk24 = src->unk1C;
            p->unk28 = src->unk20;
            p->unk38 = owner;
            p->unk34 = tmp;
            p->unk2C = a2;
            p->unk30 = a3;
            p->unk14 = 1;
            owner->unkC8 = p;
            if (src->unk0C != 0)
            {
                q = HeapAlloc(src->unk0C);
                p->unk0C = q;
                p->unk10 = *(void **)q;
            }
            return p;
        }
        p++;
        i++;
    } while (i <= 0x13);
    return 0;
}

/* fn: sub_08059D08 */
// @ 0x08059d08
void TaskDestroy(struct Unk59D08 *a)
{
    void *z;
    void *cb;

    if (a != 0)
    {
        cb = a->unk08;
        if (cb != 0)
            _08073C44(a, cb);
        z = 0;
        a->unk00 = z;
        a->unk04 = z;
        a->unk08 = z;
        a->unk14 = z;
        if (a->unk0C != 0)
        {
            HeapFree(a->unk0C);
            a->unk0C = z;
        }
    }
}
