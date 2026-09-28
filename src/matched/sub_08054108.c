#include "global.h"

// @ 0x08054108
void sub_08054108(void *a)
{
    VBlankIntrWait();
    TextWindowPopState();
    sub_08054120(a);
}

