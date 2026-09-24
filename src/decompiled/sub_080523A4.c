#include "global.h"
#include "ram_map.h"

void sub_080523A4(struct Unk2F520 *a);
void sub_080523A4(struct Unk2F520 *a)
{
  struct Unk2F520 *obj;
  struct Unk2F520Inner *slot;
  s8 *flag;
  struct Unk2F520 *new_var;
  s32 v;
  u32 base;
  if (obj)
  {
    obj = a;
    sub_08061BE8();
    sub_0805264C(obj, 0);
    sub_0805264C(obj, 1);
    sub_0805264C(obj, 2);
    sub_0805264C(obj, 3);
    sub_0805264C(obj, 4);
    sub_0805264C(obj, 5);
    slot = obj->unk288;
    flag = &(new_var = obj)->unk2D5;
    v = *flag;
    v <<= 12;
    base = 0xB0;
    base <<= 6;
    slot->unk0C = v + base;
    slot = obj->unk28C;
    v = *flag;
    v <<= 12;
    slot->unk0C = base + v;
  }
  else
  {
    obj = a;
    sub_08061BE8();
    sub_0805264C(obj, 0);
    sub_0805264C(obj, 1);
    sub_0805264C(obj, 2);
    sub_0805264C(obj, 3);
    sub_0805264C(obj, 4);
    sub_0805264C(obj, 5);
    slot = obj->unk288;
    flag = &(new_var = obj)->unk2D5;
    v = *flag;
    v <<= 12;
    base = 0xB0;
    base <<= 6;
    slot->unk0C = v + base;
    slot = obj->unk28C;
    v = *flag;
    v <<= 12;
    slot->unk0C = base + v;
  }
}
