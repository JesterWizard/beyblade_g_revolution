#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803dcfc
/* match-compiler: old_agbcc */
void *sub_0803DCFC(u32 a)
{
  u32 new_var3[2];
  u32 off;
  u8 *new_var2;
  u8 *base;
  new_var3[0] = 0;
  new_var3[1] = a;
  if (new_var3[1] <= 0x52)
  {
 do { off = new_var3[1] << 2; off += new_var3[1]; off <<= 3; base = gData_0807A1F4; new_var2 = base + off; return (void *) new_var2; } while (new_var3[0]);
  }
  DebugPrint((void *) gData_0833D1E0, (void *) gData_0833D1F4);
  return 0;
}
