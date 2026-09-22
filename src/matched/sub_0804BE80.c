#include "global.h"

// @ 0x0804be80
void sub_0804BE80(void *a)
{
    sub_08061BE8();
    sub_0804BD38(a);
    VBlankIntrWait();
    _08073C40(*(void **)0x080BB888);
}

