#include "global.h"

// @ 0x08050864
void sub_08050864(void *a)
{
    VBlankIntrWait();
    TextWindowPopState();
    DetailPanelDraw(a);
}

