#include "global.h"

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

