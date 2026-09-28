#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0807027c
// Set an object's scale (b, c) and rotation d, rebuilding its 2x2 affine
// matrix. A NULL obj takes one from the battle-object pool; the identity
// transform (d 0, scale 0x100) releases it instead. Busy objects (unk19) are
// left alone and their unk19 is returned.
struct Unk70354Object *sub_0807027C(struct Unk70354Object *obj, u16 b, u16 c, u8 d)
{
    bool32 reset;
    s32 cos, sin, sx, sy;

    reset = FALSE;
    if (d == 0 && b == 0x100 && c == b)
        reset = TRUE;
    if (obj != NULL)
    {
        if (obj->unk19 != 0)
            return (struct Unk70354Object *)(u32)obj->unk19;
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
        obj = (struct Unk70354Object *)BtlObjListMoveHeadToTail();
        if (obj == NULL)
            return NULL;
    }
    obj->unk14 = b;
    obj->unk16 = c;
    obj->unk18 = d;
    if (d != 0)
    {
        cos = gData_083C9544[d + 0x40];
        sx = gData_083A9544[b];
        obj->unk0C = (cos * sx) >> 8;
        sin = gData_083C9544[d];
        obj->unk0E = (sin * sx) >> 8;
        sin = -sin;
        sy = gData_083A9544[c];
        obj->unk10 = (sin * sy) >> 8;
        obj->unk12 = (cos * sy) >> 8;
    }
    else
    {
        obj->unk0C = gData_083A9544[b];
        obj->unk0E = d;
        obj->unk10 = d;
        obj->unk12 = gData_083A9544[c];
    }
    return obj;
}

