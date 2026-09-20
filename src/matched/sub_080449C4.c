#include "global.h"

// @ 0x080449c4

void sub_080449C4(s8 arg0)
{
    struct MainWork *work = gMainWorkPtr;

    work->unk17F0 = 0;
    work->unk17F2 = 0;
    *(u16 *)0x04000050 = 0;
    *(u16 *)0x04000052 = 0;
    *(u16 *)0x04000054 = 0;
    work->unk181B = arg0;
    sub_08043DB4(0, &gMainWorkPtr->unk036C, 0, 1, 1);
}

