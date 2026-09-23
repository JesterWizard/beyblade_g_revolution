#include "global.h"

void sub_08062F90(void)
{
    void **e0_loc;
    void **buffer_loc;
    void **palette_loc;

    if (gUnk_030008DC != 0
        || gUnk_030008D8 != 0
        || gUnk_030008E0 != 0
        || gUnk_030008D4 != 0)
        return;
    e0_loc = (void **)0x030008E0;
    buffer_loc = (void **)0x030008D4;
    *e0_loc = HeapAlloc(0x200);
    *buffer_loc = HeapAlloc(0x200);
    if (*e0_loc == 0 && *buffer_loc == 0)
        return;
    gUnk_030008DC = *(void **)*e0_loc;
    gUnk_030008D8 = *(void **)*buffer_loc;
    buffer_loc = (void **)0x030008D8;
    palette_loc = (void **)0x080BB8C0;
    _08073C4C(
        (void *)0x05000000,
        *buffer_loc,
        0x200,
        *palette_loc);
    _08073C4C(
        (void *)0x05000200,
        *buffer_loc,
        0x200,
        *palette_loc);
}
