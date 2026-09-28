#include "global.h"

// @ 0x0802fd80
void sub_0802FD80(void)
{
    sub_08061BE8();
    ItemListDraw();
    VBlankIntrWait();
    _08073C40(*(void **)0x080BB888);
}

