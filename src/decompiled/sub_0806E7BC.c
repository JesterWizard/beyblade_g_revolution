#include "global.h"

// @ 0x0806e7bc
s32 sub_0806E7BC(s32 ax, s32 ay, s32 bx, s32 by, s32 cx, s32 cy, s32 dx, s32 dy)
{
    s32 abx = ax - bx;
    s32 aby = ay - by;
    s32 cross1 = abx * (cy - by) - (cx - bx) * aby;
    s32 cross2 = abx * (dy - by) - (dx - bx) * aby;

    if (!((cross1 > 0 && cross2 < 0) || (cross1 < 0 && cross2 > 0)))
        goto no_intersect;

    {
        s32 cdx = cx - dx;
        s32 cdy = cy - dy;
        s32 cross3 = cdx * (ay - dy) - (ax - dx) * cdy;
        s32 cross4 = cdx * (by - dy) - (bx - dx) * cdy;

        if ((cross3 > 0 && cross4 < 0) || (cross3 < 0 && cross4 > 0))
            return 1;
        return 2;
    }

no_intersect:
    return 0;
}
