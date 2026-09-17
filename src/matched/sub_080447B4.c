#include "global.h"

// @ 0x080447b4
void sub_080447B4(void **a)
{
    void *p;

    while (1)
    {
        p = *a;
        a++;
        if (p == 0)
            break;
        sub_08059AE0(p);
    }
}

