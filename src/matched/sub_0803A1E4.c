#include "global.h"

// @ 0x0803a1e4
void sub_0803A1E4(void *a)
{
    VBlankIntrWait();
    sub_08061BE8();
    PartMenuRebuild(a);
    VBlankIntrWait();
    _08073C40(*(void **)0x080BB888);
}

