/* Permuter best for sub_08030F38: score 1385 (seed score 2090), 2026-09-27.
 * NOT semantic C: random mutations of src/decompiled/sub_08030F38.c, kept only as a
 * hint for the remaining difference. Do not integrate as-is. */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

void sub_08030F38(void)
{
  struct BattleWork * volatile *loc = (struct BattleWork * volatile *) ((struct BattleWork **) 0x03000290);
  struct BattleWork *work;
  struct Unk705DC *e;
  s32 i;
  s32 delta;
  struct BattleWork * volatile **new_var;
  work = *loc;
  e = work->unk0AE8.fields.unkAF0;
  if ((e != ((void *) 0)) && (((s32) e->unk0C) <= 0x7FF))
  {
    e->unk0C += 0x100;
    if (work->unk0AE8.fields.unkAF4 != ((void *) 0))
    {
      work->unk0AE8.fields.unkAF4->unk0C += 0x100;
    }
    work = *loc;
    if (work->unk0AE8.fields.unkAF8 != ((void *) 0))
    {
      work->unk0AE8.fields.unkAF8->unk0C += 0x100;
    }
    work = *loc;
    if (work->unk0AE8.fields.unkAFC != ((void *) 0))
    {
      work->unk0AE8.fields.unkAFC->unk0C += 0x100;
    }
    work = *loc;
    if (work->unk0AE8.fields.unkB40 != ((void *) 0))
    {
      work->unk0AE8.fields.unkB40->unk0C += 0x100;
    }
    work = *loc;
    if (work->unk0AE8.fields.unkB44 != ((void *) 0))
    {
      work->unk0AE8.fields.unkB44->unk0C += 0x100;
    }
    work = *loc;
    if (work->unkBA4 != ((void *) 0))
    {
      work->unkBA4->unk0C += 0x100;
    }
    work = *(*(new_var = &loc));
    if (work->unkBA8 != ((void *) 0))
    {
      work->unkBA8->unk0C += 0x100;
    }
    (*loc)->unkBB0 += 0x100;
    for (i = 0; i <= 7; i++)
    {
      work = *loc;
      if (work->unk0AE8.fields.unkB00[i] != ((void *) 0))
      {
        work->unk0AE8.fields.unkB00[i]->unk0C = work->unkBB0;
      }
      work = *loc;
      if (work->unk0AE8.fields.unkB20[i] != ((void *) 0))
      {
        work->unk0AE8.fields.unkB20[i]->unk0C = work->unkBB0;
      }
    }

  }
  work = *loc;
  e = work->unk0AE8.fields.unkB48;
  if ((e != ((void *) 0)) && (e->unk0C != work->unkBAC))
  {
    delta = work->unkBAC - e->unk0C;
    if (delta > 0x100)
    {
      delta = 0x100;
    }
    if (delta < 0x100)
    {
      delta = -0x100;
    }
    e->unk0C += delta;
    if (work->unk0AE8.fields.unkB4C != ((void *) 0))
    {
      work->unk0AE8.fields.unkB4C->unk0C += delta;
    }
  }
}
