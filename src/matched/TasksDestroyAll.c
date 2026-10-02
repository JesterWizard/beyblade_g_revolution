#include "global.h"

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

