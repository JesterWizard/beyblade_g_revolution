#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806105c
void sub_0806105C(void *a, u8 *s)
{
  u8 *sp;
  s32 i;
  u8 c;
 do { sp = s; if ((sp == 0) || (a == 0)) { return; } c = sp[0]; i = 1; } while (0);
  if (c == 0)
  {
    return;
  }
  do
  {
    sub_08060E48(a, c);
    c = sp[i];
    i++;
  }
  while (c != 0);
}
