#include "global.h"
#include "ram_map.h"

void sub_080523A4(struct Unk2F520 *a)
{
    s32 v;
    s32 base;
    struct Unk2F520Inner *obj;

    sub_08061BE8();
    sub_0805264C(a, 0);
    sub_0805264C(a, 1);
    sub_0805264C(a, 2);
    sub_0805264C(a, 3);
    sub_0805264C(a, 4);
    sub_0805264C(a, 5);
    obj = a->unk288;
    v = a->unk2D5;
    v <<= 12;
    base = 0xB0;
    base <<= 6;
    obj->unk0C = v + base;
    obj = a->unk28C;
    v = a->unk2D5;
    v <<= 12;
    obj->unk0C = v + base;
}
