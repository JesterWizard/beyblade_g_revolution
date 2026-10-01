#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080405a8
void sub_080405A8(void)
{
  struct MessageQueue **r3;
  s32 r2;
  s32 r5;
  s32 r1;
  struct MessageQueue *r0;
  u32 *slot;
  u32 tmp[1];
  struct MessageQueue *new_var;
  struct MessageQueue **r4;
  s32 i;
  tmp[0] = (u32) ((struct MessageQueue **) 0x0300047C);
  r3 = (struct MessageQueue **) tmp[0];
  r0 = *r3;
  r2 = 0x80C;
  slot = &r0->writeIndex;
  r2 = 0;
  *slot = r2;
  r1 = 0x808;
  r0 = (struct MessageQueue *) (((u8 *) r0) + r1);
  new_var = r0;
  new_var->entries[0] = (void *) r2;
  r5 = 0x1FF;
  r4 = r3;
  i = r2;
  do
  {
    if (r5)
    {
      (*(*r4)).entries[i] = (void *) (-1);
      i++;
    }
    else
    {
      (*(*r4)).entries[i] = (void *) (-1);
      i++;
    }
  }
  while (i <= r5);
}
