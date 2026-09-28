#include "global.h"

// @ 0x08056380
void sub_08056380(void *a)
{
    VBlankIntrWait();
    TextWindowPopState();
    sub_08056250(a);
}

