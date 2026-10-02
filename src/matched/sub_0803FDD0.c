#include "global.h"

// @ 0x0803fdd0

void sub_0803FDD0(s16 a)
{
    MessageQueuePush((void *)(s32)a);
    MenuPageSet(2);
    sub_0804109C((void *)((u8 *)gMainWorkPtr + 0x530), MenuPageDefGet());
    gMainWorkPtr->unk181C = 3;
}

