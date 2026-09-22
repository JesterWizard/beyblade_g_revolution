#include "global.h"

// @ 0x08048d0c
void sub_08048D0C(void *a)
{
    VBlankIntrWait();
    sub_08061BE8();
    sub_08048DB8(a);
}

