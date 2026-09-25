#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802e048
void sub_0802E048(void)
{
  u32 r0;
  u32 r1;
  u32 r2;
  u32 r3;
  u32 r4;
  struct Unk705DC *r5;
  struct Unk026C *obj;
  struct Unk705DC *rec;
  r4 = (u32) (&(*((struct Unk026C **) 0x0300026C)));
  r0 = *((u32 *) r4);
  r0 = *((u32 *) (r0 + 0x0C));
  if (r0 == 0)
  {
    goto skip_free;
  }
  BtlObjPoolFree((void *) r0);
  r1 = *((u32 *) r4);
  r0 = 0;
  *((u32 *) (r1 + 0x0C)) = r0;
  skip_free:
  r0 = 0;

  rec = BtlObjPoolAlloc((u16) r0);
  r5 = rec;
  r0 = *((u32 *) r4);
  *((struct Unk705DC **) (r0 + 0x0C)) = r5;
  r0 = (u32) ((struct MainWork **) 0x03000198);
  r0 = *((u32 *) r0);
  r1 = 0x1808;
  r0 += r1;
  r2 = *((u32 *) r0);
  r0 = 0x80;
  r0 <<= 7;
  r2 &= r0;
  if (r2 == 0)
  {
    goto use_dac;
  }
  r1 = 0x08266FE0;
  r3 = 0xFFFFC000;
  r2 = 0;
  sub_0806FF58(r5, (void *) r1, r3, r3, r2, 1, r2, r2);
  goto after_ff58;
  use_dac:
  r1 = 0x08266DAC;

  r3 = 0xFFFFC000;
  sub_0806FF58(r5, (void *) r1, r3, r3, r2, 1, r2, r2);
  after_ff58:
  r4 = (u32) (&(*((struct Unk026C **) 0x0300026C)));

  r0 = *((u32 *) r4);
  r0 = *((u32 *) (r0 + 0x0C));
  r1 = 2;
  TextEntrySetPaletteBank((struct Unk705DC *) r0, (s32) r1);
  r3 = *((u32 *) r4);
  obj = (struct Unk026C *) r3;
  r0 = (u32) obj->unk0C;
  r1 = 0;
  *((u32 *) (r0 + 8)) = r1;
  *((u32 *) (r0 + 0xC)) = r1;
  r2 = (u32) obj->unk10;
  r0 = 0xEC;
  r0 <<= 6;
  *((u32 *) (r2 + 8)) = r0;
  *((u32 *) (r2 + 0xC)) = r1;
  r0 = (u32) obj->unk14;
  r2 = 0x96;
  r2 <<= 7;
  *((u32 *) (r0 + 8)) = r2;
  r1 = 0xA8;
  r1 <<= 5;
  *((u32 *) (r0 + 0xC)) = r1;
  r0 = (u32) obj->unk18;
  r4 = 0xA0;
 do { r4 <<= 7; *((u32 *) (r0 + 8)) = r4; *((u32 *) (r0 + 0xC)) = r1; r0 = (u32) obj->unk1C; *((u32 *) (r0 + 8)) = r2; r1 = 0xC0; r1 <<= 2; *((u32 *) (r0 + 0xC)) = r1; r0 = (u32) obj->unk20; *((u32 *) (r0 + 8)) = r4; *((u32 *) (r0 + 0xC)) = r1; r1 = (u32) obj->unk24; *((u32 *) (r1 + 8)) = r2; r0 = 0xC0; r0 <<= 4; *((u32 *) (r1 + 0xC)) = r0; } while (0);
}
