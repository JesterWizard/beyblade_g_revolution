#include "global.h"

// @ 0x0802c6ac
void sub_0802C6AC(void)
{
    struct MainWork **loc;
    void *base;

    DebugPrint((void *)0x0833BE48, 0x0833BE50);
    loc = (struct MainWork **)0x03000198;
    (*loc)->unk15C8 = 0;
    (*loc)->unk15C9 = 0;
    (*loc)->unk15CA = 0;
    (*loc)->unk15CB = 0;
    (*loc)->unk15CC = 0;
    base = *loc;
    ((struct MainWork *)base)->unk15D0 = 0;
    ((struct MainWork *)base)->unk15D2 = 0;
}
