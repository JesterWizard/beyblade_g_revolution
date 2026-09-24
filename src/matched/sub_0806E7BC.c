#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806e7bc
s32 sub_0806E7BC(s32 ax, s32 ay, s32 bx, s32 by, s32 cx, s32 cy, s32 dx, s32 dy)
{
    s32 abx;
    s32 aby;
    s32 cross1;
    s32 cdx;
    s32 cdy;
    s32 cross3;
    s32 cross4;
    s32 result;

    abx = ax - bx;
    aby = ay - by;
    cross1 = abx * (cy - by) - (cx - bx) * aby;
    result = abx * (dy - by) - (dx - bx) * aby;
    if (cross1 > 0)
        goto check_cross2_pos;
    if (result < 0)
        goto fail;
    if (cross1 < 0)
        goto second;
check_cross2_pos:
    if (result > 0)
        goto fail;
second:
    cdx = cx - dx;
    cdy = cy - dy;
    cross3 = cdx * (ay - dy) - (ax - dx) * cdy;
    cross4 = cdx * (by - dy) - (bx - dx) * cdy;
    if (cross3 > 0)
        goto check_cross4;
    if (cross4 < 0)
        goto fail;
    if (cross3 < 0)
        goto success;
check_cross4:
    if (cross4 <= 0)
        goto success;
fail:
    return 0;
success:
    result = 2;
    if (cross1 >= 0)
        result = 1;
    return result;
}

