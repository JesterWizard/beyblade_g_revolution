#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_08031124 */
// @ 0x08031124
s16 ScaleRatio(s32 a, s32 b, s32 c)
{
    if (b <= 0)
        return -1;
    if (a < 0)
        a = 0;
    if (a > b)
        a = b;
    return Div(a * c, b);
}

/* fn: sub_080361A8 */
// @ 0x080361a8
void FixedEaseStep(struct Unk361A8 *a)
{
  s32 cur;
  u32 new_var;
  u32 scale = 12;
  u32 mask = 0xFFFF;
  s32 v = a->unk1C.h;
  a->unk1C.w = v;
  cur = a->unk14;
  new_var = scale;
  v = (s32) (v - cur);
  v = (s32) (v * new_var);
  v = v >> 8;
  a->unk18 = v;
  a->unk14 = (cur + v) & mask;
}

/* fn: sub_080628B4 */
// @ 0x080628b4
u32 RandRange(u32 a)
{
    u32 seed;

    seed = gMainWorkPtr->unk1800 * 0x36F1ACE3;
    gMainWorkPtr->unk1800 = seed;
    return sub_08074264((seed * 0x9FBF1) >> 16, a);
}

/* fn: sub_080674A0 */
// @ 0x080674a0
/* BIOS SWI 0x06: quotient of num/den in r0, remainder in r1. */
s32 Div(s32 num, s32 den)
{
    asm("swi 6");
    return num;
}

/* fn: sub_080674A4 */
// @ 0x080674a4
s32 DivRemainder(s32 num, s32 den)
{
    s32 rem;

    asm("swi 6" : "+r"(num), "=r"(rem) : "r"(den));
    return rem;
}

/* fn: sub_080674B0 */
// @ 0x080674b0
s32 Sqrt(s32 a)
{
    asm("swi 8");
    return a;
}

/* fn: sub_08069F00 */
// @ 0x08069f00

// @ 0x08069f00
/* match-compiler: old_agbcc */
s32 FixedMulQ8(s16 a, s16 b)
{
  s32 p = ((s32) a) * b;
  s32 r = p;
  if (p < 0)
  {
    r += 0xFF;
  }
  return (r << (p = 8)) >> (p = 16);
}

/* fn: sub_0806E7BC */
// @ 0x0806e7bc
s32 SegCrossSide(s32 ax, s32 ay, s32 bx, s32 by, s32 cx, s32 cy, s32 dx, s32 dy)
{
    s32 abx;
    s32 aby;
    s32 cross1;
    s32 cdx;
    s32 cdy;
    s32 cross3;
    s32 cross4;
    s32 result;

    abx = ax - bx;
    aby = ay - by;
    cross1 = abx * (cy - by) - (cx - bx) * aby;
    result = abx * (dy - by) - (dx - bx) * aby;
    if (cross1 > 0)
        goto check_cross2_pos;
    if (result < 0)
        goto fail;
    if (cross1 < 0)
        goto second;
check_cross2_pos:
    if (result > 0)
        goto fail;
second:
    cdx = cx - dx;
    cdy = cy - dy;
    cross3 = cdx * (ay - dy) - (ax - dx) * cdy;
    cross4 = cdx * (by - dy) - (bx - dx) * cdy;
    if (cross3 > 0)
        goto check_cross4;
    if (cross4 < 0)
        goto fail;
    if (cross3 < 0)
        goto success;
check_cross4:
    if (cross4 <= 0)
        goto success;
fail:
    return 0;
success:
    result = 2;
    if (cross1 >= 0)
        result = 1;
    return result;
}
