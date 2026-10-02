#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_08040530 */
// @ 0x08040530
void MessageLinesFree(void)
{
    StringArrayFree(gUnk_0300047C->lines, 9);
}

/* fn: sub_080405A8 */
// @ 0x080405a8
void MessageQueueReset(void)
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

/* fn: sub_080405E8 */
// @ 0x080405e8
void MessageQueuePush(void *a)
{
    struct MessageQueue *p;
    u32 n;

    p = gUnk_0300047C;
    n = p->writeIndex;
    if ((s32)n <= 0x1FE)
    {
        p->entries[n] = a;
        p->writeIndex = n + 1;
    }
}

/* fn: sub_08040618 */
// @ 0x08040618
s32 MessageQueuePopKeyedWord(void)
{
    struct MessageQueue *p;
    u32 n;
    s32 v;

    p = gUnk_0300047C;
    n = p->readIndex;
    v = (s32)p->entries[n];
    p->readIndex = n + 1;
    if (v >= 0)
        return GetPlayerKeyedWord((void *)v);
    return 0;
}

/* fn: sub_08040680 */
// @ 0x08040680

void MessageBoxLoadNext(struct MessageBox *a)
{
    s32 i;
    s32 value;
    u32 d;
    u16 y;
    u16 f;

    if (a->unk274 != NULL)
    {
        BtlObjPoolFree(a->unk274);
        a->unk274 = NULL;
    }
    for (i = 0; i <= 8; i++)
        MemClear(gUnk_0300047C->lines[i], 0x60);
    value = MessageQueuePopKeyedWord();
    {
        u8 *buf = StringAlloc(0x400);
        gUnk_0300047C->scratch = buf;
        _080408E4(value, buf);
    }
    TextSetActiveObject((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    d = TextGetWidthTable();
    y = TextGetAreaWidth() - 0x28;
    f = TextGetGlyphWidth();
    a->lineCount = SplitStringIntoStringArray(gUnk_0300047C->lines, gUnk_0300047C->scratch, 9, d, y, f, TextGetSpacing(), 0x60);
    StringFree(gUnk_0300047C->scratch);
    a->curLine = 0;
    TextTypewriterResume((struct Unk61BDC *)a->unk220->unk00);
    TextWindowPopState();
    TextTypewriterRestart((struct Unk61E40 *)a->unk220->unk00);
    if (gMainWorkPtr->unk184F != 0)
        *(u32 *)0x03000474 = 1;
    else
        *(u32 *)0x03000474 = 2;
}
