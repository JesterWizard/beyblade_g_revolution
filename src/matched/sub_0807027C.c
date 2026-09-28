#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0807027c
// Set an object's scale (b, c) and rotation d, rebuilding its 2x2 affine
// matrix. A NULL obj takes one from the battle-object pool; the identity
// transform (d 0, scale 0x100) releases it instead. Busy objects (unk19) are
// left alone and their unk19 is returned.
struct AffineObj *BtlObjSetAffine(struct AffineObj *obj, u16 b, u16 c, u8 d)
{
    bool32 reset;
    s32 cos, sin, sx, sy;

    reset = FALSE;
    if (d == 0 && b == 0x100 && c == b)
        reset = TRUE;
    if (obj != NULL)
    {
        if (obj->locked != 0)
            return (struct AffineObj *)(u32)obj->locked;
        if (reset)
        {
            BtlObjListMoveToHead((struct BtlObj *)obj);
            return NULL;
        }
    }
    else
    {
        if (reset)
            return NULL;
        obj = (struct AffineObj *)BtlObjListMoveHeadToTail();
        if (obj == NULL)
            return NULL;
    }
    obj->scaleX = b;
    obj->scaleY = c;
    obj->angle = d;
    if (d != 0)
    {
        cos = gData_083C9544[d + 0x40];
        sx = gData_083A9544[b];
        obj->pa = (cos * sx) >> 8;
        sin = gData_083C9544[d];
        obj->pb = (sin * sx) >> 8;
        sin = -sin;
        sy = gData_083A9544[c];
        obj->pc = (sin * sy) >> 8;
        obj->pd = (cos * sy) >> 8;
    }
    else
    {
        obj->pa = gData_083A9544[b];
        obj->pb = d;
        obj->pc = d;
        obj->pd = gData_083A9544[c];
    }
    return obj;
}

