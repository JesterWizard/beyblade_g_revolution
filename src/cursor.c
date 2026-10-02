#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0804245C */
// @ 0x0804245c
/* match-compiler: old_agbcc */

void CursorHistoryReplayStep(void)
{
    s8 index;
    u16 value;

    if (gMainWorkPtr->unk182C == 0)
        return;
    if (gMainWorkPtr->unk180C == 0 || gMainWorkPtr->unk180C == 0x10)
    {
        sub_080424E8();
        return;
    }

    index = (s8)gUnk_03000538->readIndex;
    value = gUnk_03000538->dir[(s32)index];
    switch (value)
    {
    case 1:
        CursorReplayStepRight();
        break;
    case 2:
        CursorReplayStepLeft();
        break;
    case 4:
        sub_08042630();
        break;
    case 8:
        sub_080426A4();
        break;
    }
    gUnk_03000538->readIndex = gUnk_03000538->readIndex + 1;
    {
        u8 *base;
        u8 *ring;
        u8 mask;
        u8 v;

        base = &gUnk_03000538->readIndex;
        ring = base;
        mask = 0x1F;
        v = *ring;
        mask &= v;
        *ring = mask;
    }
}

/* fn: sub_08042540 */
// @ 0x08042540

void CursorReplayStepRight(void)
{
    u8 *addr;
    u32 mask;
    u32 value;

    addr = &gMainWorkPtr->unk0479;
    mask = 2;
    value = *addr;
    mask &= value;
    *addr = (u8)mask;
    gUnk_03000538->facing = 0x40;
    if (gMainWorkPtr->unk0462 != 8)
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk0448, 8);
    gMainWorkPtr->unk044C =
        gUnk_03000538->x[(s32)(s8)gUnk_03000538->readIndex];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->y[(s32)(s8)gUnk_03000538->readIndex];
}

/* fn: sub_080425B8 */
// @ 0x080425b8
void CursorReplayStepLeft(void)
{
  u8 *addr;
  u8 mask;
  u8 value;
 // The do/while(0) block is load-bearing: splitting `addr` and `mask` into
 // separate statements changes the register assignment (retail wants the
 // 0x03000198 load before the 0x03000538 load).
 do { addr = &gMainWorkPtr->unk0479; mask = 1; } while (0);
  value = *addr;
  mask |= value;
  *addr = mask;
  gUnk_03000538->facing = 0x20;
  if (gMainWorkPtr->unk0462 != 8)
  {
    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gMainWorkPtr->unk0448), 8);
  }
  gMainWorkPtr->unk044C = gUnk_03000538->x[(s32) ((s8) gUnk_03000538->readIndex)];
  gMainWorkPtr->unk0450 = gUnk_03000538->y[(s32) ((s8) gUnk_03000538->readIndex)];
}

/* fn: sub_08042630 */
// @ 0x08042630

void sub_08042630(void)
{
    gMainWorkPtr->unk0479 = 0;
    gUnk_03000538->facing = 0x80;
    if (gMainWorkPtr->unk0462 != 0x0A)
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk0448, 0x0A);
    gMainWorkPtr->unk044C =
        gUnk_03000538->x[(s32)(s8)gUnk_03000538->readIndex];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->y[(s32)(s8)gUnk_03000538->readIndex];
}

/* fn: sub_080426A4 */
// @ 0x080426a4

void sub_080426A4(void)
{
    gMainWorkPtr->unk0479 = 0;
    gUnk_03000538->facing = 0x100;
    if (gMainWorkPtr->unk0462 != 0x0B)
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk0448, 0x0B);
    gMainWorkPtr->unk044C =
        gUnk_03000538->x[(s32)(s8)gUnk_03000538->readIndex];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->y[(s32)(s8)gUnk_03000538->readIndex];
}

/* fn: sub_08042784 */
// @ 0x08042784
// Push {a, cursor x, cursor y} onto the 32-slot history ring at *gUnk_03000538
// while recording is enabled (MainWork.unk182C).
void CursorHistoryPush(u32 a)
{
    struct CursorHistory *ring = gUnk_03000538;
    s32 i = (s8)ring->writeIndex;
    struct MainWork *work = gMainWorkPtr;

    if (work->unk182C != 0)
    {
        ring->dir[i] = a;
        ring->x[i] = work->unk0370;
        ring->y[i] = work->unk0374;
        i++;
        ring->writeIndex = i & 0x1F;
    }
}

/* fn: sub_080427E8 */
// @ 0x080427e8
/* match-compiler: old_agbcc */
void CursorFaceIdlePose(void)
{
    struct MainWork *main;

    main = gMainWorkPtr;
    if (main->unk182C == 0)
        return;
    switch (gUnk_03000538->facing)
    {
    case 0x40:
        if (main->unk0462 != 5)
            AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&main->unk0448, 5);
        gMainWorkPtr->unk0479 = 2 & gMainWorkPtr->unk0479;
        break;
    case 0x20:
        if (main->unk0462 != 5)
            AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&main->unk0448, 5);
        gMainWorkPtr->unk0479 = 1 | gMainWorkPtr->unk0479;
        break;
    case 0x80:
        if (main->unk0462 != 6)
            AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&main->unk0448, 6);
        gMainWorkPtr->unk0479 = 0;
        break;
    case 0x100:
        if (main->unk0462 != 7)
            AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&main->unk0448, 7);
        gMainWorkPtr->unk0479 = 0;
        break;
    }
}

/* fn: sub_080428C4 */
// @ 0x080428c4
/* match-compiler: old_agbcc */

// @ 0x080428c4
// If bit 0x2000 of unk1808 is clear, zero the two bytes of the 0x03000538 object.
void CursorHistoryReset(void)
{
    u32 v = gMainWorkPtr->unk1808 & 0x2000;

    if (v != 0)
        return;
    gUnk_03000538->readIndex = v;
    gUnk_03000538->writeIndex = v;
}

/* fn: sub_080428F0 */
// @ 0x080428f0

extern void CursorHistoryReset(void);

// @ 0x080428f0
void CursorHistoryFillLine(u32 a, u32 b, u32 c, u32 d)
{
    struct CursorHistory *ring;
    struct CursorHistory **ringSlot;
    s32 i;
    u32 step;
    u32 stepBack;

    if (gMainWorkPtr->unk1808 & 0x2000)
        return;
    CursorHistoryReset();
    i = 0;
    stepBack = 0xFFFFFF00;
    step = 0x100;
    ringSlot = &gUnk_03000538;
    do
    {
        ring = *ringSlot;
        ring->dir[i] = (u16)d;
        ring->x[i] = a;
        ring->y[i] = b;
        ring->writeIndex++;
        switch (c)
        {
        case 0:
            a += stepBack;
            break;
        case 1:
            a += step;
            break;
        case 2:
            b += stepBack;
            break;
        case 3:
            b += step;
            break;
        }
        i++;
    } while (i <= 15);
}

/* fn: sub_080429C0 */
// @ 0x080429c0

// @ 0x080429c0
u32 CursorHistoryGet(void)
{
    return (u32)gUnk_03000538;
}

/* fn: sub_080429CC */
// @ 0x080429cc
void CursorHistoryStartLine(void)
{
    struct CursorHistory *ring;
    struct MainWork *main;
    u32 x;
    u32 y;

    ring = gUnk_03000538;
    main = gMainWorkPtr;
    ring->facing = main->unk1810;
    switch (main->unk1828)
    {
    case 0:
        x = main->unk17B4 = main->unk0370 + 0x1000;
        y = main->unk17B8 = main->unk0374;
        CursorHistoryFillLine(x, y, 0, 1);
        break;
    case 1:
        x = main->unk17B4 = main->unk0370 - 0x1000;
        y = main->unk17B8 = main->unk0374;
        CursorHistoryFillLine(x, y, 1, 2);
        break;
    case 2:
        x = main->unk17B4 = main->unk0370;
        y = main->unk17B8 = main->unk0374 + 0x1000;
        CursorHistoryFillLine(x, y, 2, 4);
        break;
    case 3:
        x = main->unk17B4 = main->unk0370;
        y = main->unk17B8 = main->unk0374 - 0x1000;
        CursorHistoryFillLine(x, y, 3, 8);
        break;
    }
}

/* fn: sub_08047624 */
// @ 0x08047624
/* match-compiler: old_agbcc */
// Count the pixel steps from the cursor (MainWork x/y >> 8) to the next
// 8-pixel boundary in direction `mode` (0 = -x, 1 = +x, 2 = -y, 3 = +y).
s32 CursorStepsToTile(u32 mode)
{
    u8 dir = mode;
    s32 x = gMainWorkPtr->unk0370 >> 8;
    s32 y = gMainWorkPtr->unk0374 >> 8;
    s32 steps = 0;
    s32 pos;

    switch (dir)
    {
    case 0:
        pos = x - 1;
        while ((pos & 7) != 0)
        {
            pos--;
            steps++;
        }
        return steps;
    case 1:
        pos = x + 1;
        while ((pos & 7) != 0)
        {
            pos++;
            steps++;
        }
        return steps;
    case 2:
        pos = y - 1;
        while ((pos & 7) != 0)
        {
            pos--;
            steps++;
        }
        return steps;
    case 3:
        pos = y + 1;
        while ((pos & 7) != 0)
        {
            pos++;
            steps++;
        }
        return steps;

    }
    // BUG: no return for other modes (r0 still holds y).
#ifdef BUGFIX
    return 0;
#endif
}

/* fn: sub_08057274 */
// @ 0x08057274
/* match-compiler: old_agbcc */
// Map the current input direction (MainWork.unk1810) to the cursor entity
// animation (keys 5/6/7) and update its facing flags.
void CursorFaceIdlePoseFromFacing(void)
{
    switch (gMainWorkPtr->unk1810)
    {
    case 0x40:
        if (gMainWorkPtr->unk0386 != 5)
            AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 5);
        gMainWorkPtr->unk039D &= 2;
        break;
    case 0x20:
        if (gMainWorkPtr->unk0386 != 5)
            AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 5);
        gMainWorkPtr->unk039D |= 1;
        break;
    case 0x80:
        if (gMainWorkPtr->unk0386 != 6)
            AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 6);
        gMainWorkPtr->unk039D = 0;
        break;
    case 0x100:
        if (gMainWorkPtr->unk0386 != 7)
            AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 7);
        gMainWorkPtr->unk039D = 0;
        break;
    }
}
