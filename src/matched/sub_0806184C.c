#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806184c
/* match-compiler: old_agbcc */
void sub_0806184C(u16 x, u16 y)
{
  void *new_var;
  struct TextWindow *work;
  u16 width;
  u32 bank;
  int new_var2;
  void *destination;
  work = *((struct TextWindow **) 0x03000798);
  if (y >= ((work->height >> 3) - 1))
  {
    return;
  }
  width = work->width >> 3;
  if (x >= (width - 1))
  {
    return;
  }
  new_var = (void *) 0;
  bank = work->charBlock;
  new_var2 = 0x6000000 + (bank << 14);
  destination = (void *) ((new_var2 + ((((u32) width) << 5) * y)) + (x << 5));
  _08073C4C(new_var, destination, 0x20, *((void **) 0x080BB8BC));
}
