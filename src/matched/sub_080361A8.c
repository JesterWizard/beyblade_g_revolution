#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080361a8
void sub_080361A8(struct Unk361A8 *a)
{
  s32 cur;
  u32 new_var;
  u32 scale = 12;
  u32 mask = 0xFFFF;
  s32 v = a->unk1C.h;
  a->unk1C.w = v;
  cur = a->unk14;
  new_var = scale;
  v = (s32) (v - cur);
  v = (s32) (v * new_var);
  v = v >> 8;
  a->unk18 = v;
  a->unk14 = (cur + v) & mask;
}
