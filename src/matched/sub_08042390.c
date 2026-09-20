#include "global.h"

// @ 0x08042390
s32 sub_08042390(struct Unk42390 *arg0)
{
    s32 y;
    s32 x;
    s32 py;
    s32 px;
    s32 d;

    y = arg0->unk04 >> 8;
    x = arg0->unk08 >> 8;
    py = (s32)gMainWorkPtr->unk0370 >> 8;
    px = (s32)gMainWorkPtr->unk0374 >> 8;

    if (py >= y)
        goto py_ge;
    if (px >= x)
        goto py_lt_px_ge;
    d = y - py;
    if (d <= 0xB)
        goto ret1;
    goto ret3;

py_lt_px_ge:
    d = y - py;
    if (d <= 0xB)
        goto ret0;
ret3:
    return 3;

py_ge:
    if (px >= x)
        goto py_ge_px_ge;
    d = py - y;
    if (d > 0xB)
        goto ret2;
ret1:
    return 1;

py_ge_px_ge:
    d = py - y;
    if (d <= 0xB)
        goto ret0;
ret2:
    return 2;

ret0:
    return 0;
}

