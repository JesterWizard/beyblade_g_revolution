#include "global.h"

// @ 0x08045128
void sub_08045128(u8 arg0)
{
  u32 r0;
  u32 r1;
  u32 r2;
  u32 r3;
  u32 r4;
  u32 *new_var;
  r0 = arg0;
  r1 = (u32) ((struct MainWork **) 0x03000198);
  r3 = *((u32 *) r1);
  r1 = 0x1688;
  r2 = r3 + r1;
  r1 = r0 << 1;
  r1 += r0;
  r1 <<= 3;
  r2 = *((u32 *) r2);
  r2 += r1;
  r1 = 0x168C;
  r4 = r3 + r1;
  r1 = r0 << 6;
  r1 -= r0;
  r1 <<= 2;
  r1 -= r0;
  new_var = &r1;
  r1 <<= 5;
  r0 = *((u32 *) r4);
  r0 += r1;
  r1 = 0x1788;
  r3 += r1;
  r1 = *((u32 *) (r2 + 8));
  *((u32 *) r3) = r1;
  r1 = 0;
  sub_08045590((void *) r0, (u8) (*new_var));
}

