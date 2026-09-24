/* match-compiler: old_agbcc */
#include "global.h"
#include "data_symbols.h"

s32 sub_0803E2AC(struct Unk3E328 *a);
extern u8 gData_0807B6F0[];
extern u8 gData_0807BB80[];
extern u8 gData_0807BDB8[];
s32 sub_0803E2AC(struct Unk3E328 *a)
{
  const u8 *t1;
  const u8 *t2;
  const u8 *t3;
  const u8 *e1;
  s8 new_var2;
  const u8 *e2;
  const u8 *e3;
  s32 red;
  int new_var3;
  int new_var;
  s32 green;
  s32 blue;
  if (a == 0)
  {
    return 0;
  }
  t1 = gData_0807BDB8;
  new_var2 = a->unk1D;
  e1 = t1 + (a->unk1E * 4);
  t2 = gData_0807BB80;
  e2 = t2 + (((s8) a->unk20) * 4);
  new_var3 = e2[2] + e1[2];
  red = e2[0] + e1[0];
  green = (new_var = e2[1] + e1[1]);
  blue = new_var3;
  t3 = gData_0807B6F0;
  e3 = t3 + (new_var2 * 4);
  red += e3[0];
  green += e3[1];
  blue += e3[2];
  if (red > 8)
  {
    return 0;
  }
  if (green > 8)
  {
    return 1;
  }
  if ((green > 5) && (blue > 5))
  {
    return 2;
  }
  return 3;
}
