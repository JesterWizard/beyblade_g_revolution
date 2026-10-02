#include "global.h"

// @ 0x080400d4
void sub_080400D4(void *a)
{
    u32 v;

    MenuPageSet(2);
    v = (u32)MenuPageDefGet();
    sub_08041774(a, (void *)v, 2);
}

