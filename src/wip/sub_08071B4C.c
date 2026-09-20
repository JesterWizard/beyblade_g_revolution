#include "global.h"

void sub_08071B4C(void)
{
    u16 idx;
    void **handlerSlot;
    void *list;

    *(u16 *)0x04000084 = 0;
    *(u16 *)0x04000082 = 0;
    *(u32 *)0x040000C4 = 0;
    *(u32 *)0x040000D0 = 0;
    *(u32 *)0x04000104 = 0;
    *(u32 *)0x04000100 = 0;

    handlerSlot = (void **)0x080BB8BC;
    list = *(void **)gUnk_030040DC;

    idx = *(u16 *)gUnk_0300410C;
    _08073C4C((void *)0, list, (idx << 1) + 0x20 + idx, *handlerSlot);

    *(s32 *)gUnk_030000C0 = 0;
}
