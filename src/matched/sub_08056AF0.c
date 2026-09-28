#include "global.h"

// @ 0x08056af0
void sub_08056AF0(void *a)
{
    VBlankIntrWait();
    TextWindowPopState();
    sub_08056BA4(a);
}

