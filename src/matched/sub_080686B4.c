#include "global.h"

// @ 0x080686b4
void SceneObjGetPosition(struct Actor *a, u32 *b)
{
    if (a->positionFn != 0)
        _08073C4C(a, b, (u32)a, a->positionFn);
    else
    {
        b[0] = a->x;
        b[1] = a->y;
        b[2] = a->z;
    }
}

