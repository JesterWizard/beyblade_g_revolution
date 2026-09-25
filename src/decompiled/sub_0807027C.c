#include "global.h"
#include "data_symbols.h"

// @ 0x0807027C
/* Init or refresh Unk70354Object scale/rotation from angle tables. */
struct Unk70354Object *sub_0807027C(void *a, u16 b, u16 c, u8 d)
{
    struct Unk70354Object *obj;
    u32 special;
    s16 cosVal;
    s16 sinVal;
    s16 scaleB;
    s16 scaleC;

    obj = a;
    special = 0;
    if (d == 0 && b == 0x100 && c == b)
        special = 1;

    if (obj != NULL)
    {
        if (obj->unk19 != 0)
            return (struct Unk70354Object *)(u32)obj->unk19;
        if (special != 0)
        {
            sub_0806FF28((struct BtlObj *)obj);
            return NULL;
        }
    }
    else
    {
        if (special != 0)
            return NULL;
        obj = (struct Unk70354Object *)sub_0806FEFC();
        if (obj == NULL)
            return NULL;
    }

    obj->unk14 = b;
    obj->unk16 = c;
    obj->unk18 = d;
    if (d != 0)
    {
        cosVal = gData_083C9544[d + 0x40];
        scaleB = gData_083A9544[b];
        obj->unk0C = (cosVal * scaleB) >> 8;
        sinVal = gData_083C9544[d];
        obj->unk0E = (sinVal * scaleB) >> 8;
        sinVal = -sinVal;
        scaleC = gData_083A9544[c];
        obj->unk10 = (sinVal * scaleC) >> 8;
        obj->unk12 = (cosVal * scaleC) >> 8;
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
