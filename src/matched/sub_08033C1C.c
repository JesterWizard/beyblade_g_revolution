#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08033c1c
void sub_08033C1C(void)
{
  u32 *new_var;
  struct Unk0380 *r1;
  u32 tmp[1];
  new_var = &tmp[0];
  tmp[0] = 0x03000380;
  r1 = (struct Unk0380 *) (*new_var);
  if (r1->unk09 == 1)
  {
    r1->unk09 = 0;
    r1->unk0A = 0;
    sub_080358CC(&r1->unk0C);
  }
}
