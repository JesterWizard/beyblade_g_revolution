#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08069f00
/* match-compiler: old_agbcc */
s32 sub_08069F00(s16 a, s16 b)
{
  s32 p = ((s32) a) * b;
  s32 r = p;
  if (p < 0)
  {
    r += 0xFF;
  }
  return (r << (p = 8)) >> (p = 16);
}
