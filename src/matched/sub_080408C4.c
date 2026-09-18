#include "global.h"

// @ 0x080408c4
s32 sub_080408C4(void)
{
    s8 buf[12];

    sub_0802C314(1, 1, buf);
    return sub_0803DD88(buf[0]);
}

