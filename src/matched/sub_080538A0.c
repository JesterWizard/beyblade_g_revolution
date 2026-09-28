#include "global.h"

// @ 0x080538a0
void sub_080538A0(void *a)
{
    VBlankIntrWait();
    TextWindowPopState();
    sub_08053690(a);
}

