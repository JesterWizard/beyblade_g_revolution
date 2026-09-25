#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042b78
s32 ExpBracketTop(s32 level)
{
  s32 key;
  s32 minusOne;
  s32 sentinel;
  const u32 *base;
  const u32 *entry;
  s32 first;
  key = level;
  base = (const u32 *) 0x080908BC;
  first = (s32) base[0];
  minusOne = -1;
  if (first != minusOne)
  {
    sentinel = minusOne;
    entry = base;
    for (;;)
    {
      if (base[0] == ((u32) key))
        return entry[3];
      entry += 2;
      base += 2;
      if (entry[0] == ((u32) sentinel))
        break;
    }

  }
  return -1;
}
