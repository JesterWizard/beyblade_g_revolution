/* Permuter best for sub_0802DCDC: score 95 (seed score ?), 2026-09-27.
 * NOT semantic C: random mutations of src/decompiled/sub_0802DCDC.c, kept only as a
 * hint for the remaining difference. Do not integrate as-is. */
#include "global.h"
#include "ram_map.h"

void sub_0802DCDC(void *arg)
{
  struct MainWork *main;
  struct Unk026C *new_var2[2];
  struct Unk42E78 *row;
  struct Unk310F0b *tens;
  struct Unk310F0b *ones;
  u32 flags;
  u32 x;
  u32 y;
  s16 current;
  s8 t;
  u32 *palette;
  main = *((struct MainWork **) 0x03000198);
  flags = main->unk1808;
  if (flags & 4)
  {
    return;
  }
  if (flags & 0x1000)
  {
    return;
  }
  main->unk1808 = 0x1000;
  main->unk1808 = flags | main->unk1808;
  current = main->unk1838;
  if (current == (-1))
  {
    return;
  }
  new_var2[0] = *((struct Unk026C **) 0x0300026C);
  if (((s8) new_var2[0]->unk48) == (-1))
  {
    new_var2[0]->unk4C = current;
    new_var2[0]->unk4E = main->unk183A;
    new_var2[0]->unk48 = 0;
    (*((struct Unk026C **) 0x0300026C))->unk04 = 1;
    (*((struct Unk026C **) 0x0300026C))->unk44 = arg;
    new_var2[1] = *((struct Unk026C **) 0x0300026C);
    (*((struct MainWork **) 0x03000198))->unk16D4 = sub_08042B00(new_var2[1]->unk4E);
    return;
  }
  if ((current == new_var2[0]->unk4C) || (((s8) new_var2[0]->unk48) != 2))
  {
    return;
  }
  row = (struct Unk42E78 *) sub_08042E78((s16) main->unk183A);
  new_var2[0] = *((struct Unk026C **) 0x0300026C);
  x = new_var2[0]->unk28->unk08;
  y = new_var2[0]->unk28->unk0C;
  main = *((struct MainWork **) 0x03000198);
  new_var2[0]->unk4C = main->unk1838;
  new_var2[0]->unk4E = main->unk183A;
  new_var2[0]->unk44 = arg;
  (*((struct MainWork **) 0x03000198))->unk16D4 = sub_08042B00(new_var2[0]->unk4E);
  if ((*((struct Unk026C **) 0x0300026C))->unk28 != ((void *) 0))
  {
    sub_0806FE84((*((struct Unk026C **) 0x0300026C))->unk28);
    (*((struct Unk026C **) 0x0300026C))->unk28 = (void *) 0;
  }
  (*((struct Unk026C **) 0x0300026C))->unk28 = sub_0806FDD0(1);
  sub_0806FF58((*((struct Unk026C **) 0x0300026C))->unk28, sub_08042B28((*((struct Unk026C **) 0x0300026C))->unk4E), x, y, 0, 1, 1, 0);
  palette = gData_080BB8C0;
  _08073C4C(sub_08042B50((*((struct Unk026C **) 0x0300026C))->unk4E), (void *) 0x05000380, 0x20, (void *) (*palette));
  sub_080705DC((*((struct Unk026C **) 0x0300026C))->unk28, 0x0C);
  sub_0802E18C((struct Unk310F0b *) (*((struct Unk026C **) 0x0300026C))->bladeStrengthTens, (struct Unk310F0b *) (*((struct Unk026C **) 0x0300026C))->bladeStrengthOnes, (s8) row->strength);
  tens = (struct Unk310F0b *) (*((struct Unk026C **) 0x0300026C))->bitBeastLevelTens;
  ones = (struct Unk310F0b *) (*((struct Unk026C **) 0x0300026C))->bitBeastLevelOnes;
  t = sub_0802E210();
  sub_0802E18C(tens, ones, t);
  t = sub_0802E1B4(row->bitBeastExp);
  (*((struct Unk026C **) 0x0300026C))->bitBeastExpBar->unk18 = t;
}
