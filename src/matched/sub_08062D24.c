#include "global.h"

// @ 0x08062d24
void sub_08062D24(u32 idx, u8 *out)
{
  u32 shifted = idx << 24;
  u32 *new_var;
  u32 base = 0x05000000;
  u16 color;
  shifted = shifted >> 23;
  new_var = &shifted;
  shifted = (*new_var) + base;
  color = *((u16 *) shifted);
  out[0] = color & 0x1F;
  out[1] = (color & 0x3E0) >> 5;
  out[2] = (color & 0x7C00) >> 10;
}

