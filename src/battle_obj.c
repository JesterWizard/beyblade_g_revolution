#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0806F910 */
// @ 0x0806f910
// Battle object system init: (re)allocate the object pool (nObj <= 0x80 nodes
// of 0x34), the OAM sprite-slot pool (nSpr <= 0x20 nodes of 0x1C) and the
// VRAM span list, link each into a free list, then hide all OAM entries.
#define HeapAllocBlock(size) ((struct Unk6F910Block *(*)(u32))FastAllocate)(size)

void BtlObjSystemInit(u32 nObj, u32 nSpr)
{
    struct Unk700CCNode *node;
    struct Unk6F910Spr *spr;
    void *prev;
    struct Unk6FBF8Span *span;
    u32 oam;
    s32 i;

    gData_03004164 = 0x800;
    gData_0300415C = 0;
    if (nObj > 0x80)
        nObj = 0x80;
    if (nSpr > 0x20)
        nSpr = 0x20;
    if (gData_030040A0 != NULL)
    {
        HeapFree(gData_030040A0);
        gData_030040A0 = NULL;
    }
    if (gData_0300409C != NULL)
    {
        HeapFree(gData_0300409C);
        gData_0300409C = NULL;
    }
    if (gData_03004094 != NULL)
    {
        HeapFree(gData_03004094);
        gData_03004094 = NULL;
    }
    if (nObj != 0)
    {
        gData_030040A0 = HeapAllocBlock(0x34 * nObj);
        if (gData_030040A0 == NULL)
            DebugMessage((void *)0x083D20C8);
    }
    if (nSpr != 0)
    {
        gData_0300409C = HeapAllocBlock(nSpr * 0x1C);
        if (gData_0300409C == NULL)
            DebugMessage((void *)0x083D20E4);
    }
    gData_03004094 = HeapAllocBlock(0x100);
    if (gData_03004094 == NULL)
    {
        DebugPrint((void *)0x083D2108);
        gData_0300408C = NULL;
    }
    else
        gData_0300408C = gData_03004094->unk00;
    if (gData_030040A0 != NULL)
        gData_03004090 = gData_030040A0->unk00;
    else
        gData_03004090 = NULL;
    if (gData_0300409C != NULL)
        gData_030040B0 = gData_0300409C->unk00;
    else
        gData_030040B0 = NULL;
    if (gData_03004090 != NULL)
        ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, gData_03004090, gData_030040A0->unk04);
    if (gData_030040B0 != NULL)
        ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, gData_030040B0, gData_0300409C->unk04);
    if (nObj != 0)
    {
        node = gData_03004090;
        spr = gData_030040B0;
        prev = NULL;
        for (i = nObj - 2; i != -1; i--)
        {
            node->unk00 = prev;
            node->unk04 = node + 1;
            node->unk24 = -1;
            prev = node;
            node++;
        }
        node->unk00 = prev;
        node->unk04 = NULL;
        gData_030040A4 = NULL;
        gData_030040AC = (struct Unk6FDB4 *)gData_03004090;
        gData_030040B4 = nObj;
    }
    if (nSpr != 0)
    {
        prev = NULL;
        oam = 0x07000000;
        for (i = nSpr - 2; i != -1; i--)
        {
            spr->unk00 = prev;
            spr->unk04 = spr + 1;
            spr->unk08 = oam;
            oam += 0x20;
            prev = spr;
            spr++;
        }
        spr->unk00 = prev;
        spr->unk04 = NULL;
        spr->unk08 = oam;
        *(void **)gData_030040B8 = NULL;
        *(void **)gData_030040A8 = gData_030040B0;
    }
    if (gData_0300408C != NULL)
    {
        gData_03004088 = gData_0300408C;
        gData_03004098 = gData_0300408C + 1;
        gData_0300408C->start = 0;
        gData_0300408C->size = 0x400;
        gData_0300408C->next = NULL;
        span = gData_0300408C + 1;
        for (i = 29; i != -1; i--)
        {
            span->next = span + 1;
            span++;
        }
        span->next = NULL;
    }
    ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0xA0, (void *)0x07000000, 0x400);
}

/* fn: sub_0806FDB4 */
// @ 0x0806fdb4
/* match-compiler: old_agbcc */
struct Unk6FDB4 *BtlObjListFindInsertPoint(struct Unk6FDB4 *p, u16 key)
{
    struct Unk6FDB4 *prev = 0;

    if (p != 0)
    {
        do
        {
            if (p->unk22 >= key)
                break;
            prev = p;
            p = p->unk04;
        } while (p != 0);
    }
    return prev;
}

/* fn: sub_0806FDD0 */
// @ 0x0806fdd0
/* match-compiler: old_agbcc */
void *BtlObjPoolAlloc(u16 key_arg)
{
    u16 key;
    struct Unk6FDB4 *node;
    struct Unk6FDB4 **head_loc;
    struct Unk6FDB4 **free_loc;
    struct Unk6FDB4 *previous;

    key = key_arg;
    free_loc = (struct Unk6FDB4 **)0x030040AC;
    node = *free_loc;
    if (node != 0)
    {
        head_loc = (struct Unk6FDB4 **)0x030040A4;
        previous = BtlObjListFindInsertPoint(*head_loc, key);
        node->unk22 = key;
        *free_loc = node->unk04;
        if (previous == 0)
        {
            if (*head_loc != 0)
                (*head_loc)->unk00 = node;
            node->unk04 = *head_loc;
            node->unk00 = 0;
            *head_loc = node;
        }
        else
        {
            if (previous->unk04 != 0)
                previous->unk04->unk00 = node;
            node->unk04 = previous->unk04;
            node->unk00 = previous;
            previous->unk04 = node;
        }
        gUnk_030040B4--;
    }
    else
        DebugMessage((void *)0x083D2230);
    LinkedListValidate((struct Unk6F8C4 *)gUnk_030040A4);
    return node;
}

/* fn: sub_0806FE84 */
// @ 0x0806fe84
/* match-compiler: old_agbcc */

void BtlObjPoolFree(void *arg)
{
    struct Unk6FE84 *state;
    struct Unk6FE84 *previous;
    struct Unk6FE84 *next;
    s32 status;
    s32 bit;

    state = arg;
    previous = state->unk00;
    next = state->unk04;
    status = state->unk24;
    if (status >= 0 && (state->unk20 & 1) == 0)
    {
        bit = 1 << (state->unk16 - 5);
        VramSpanFree(status, bit);
    }
    state->unk24 = -1;
    if (previous != 0)
        previous->unk04 = next;
    else
        *(struct Unk6FE84 **)(void *)&gUnk_030040A4 = next;
    if (next != 0)
        next->unk00 = previous;
    {
        struct Unk6FE84 **free_loc;

        free_loc = (struct Unk6FE84 **)(void *)&gUnk_030040AC;
        state->unk04 = *free_loc;
        *free_loc = state;
    }
    if (state->unk30 != 0)
    {
        BtlObjListMoveToHead((struct BtlObj *)state->unk30);
        state->unk30 = 0;
    }
    gUnk_030040B4++;
    LinkedListValidate((struct Unk6F8C4 *)(*(void **)(void *)&gUnk_030040A4));
}

/* fn: sub_0806FEFC */
// @ 0x0806fefc
/* match-compiler: old_agbcc */

// @ 0x0806fefc
// Pop the head node off the battle-object list and push it onto the tail list.
// gData_030040A8/gData_030040B8 symbols (not raw literals) stop agbcc folding
// 0x030040B8 into 0x030040A8+0x10.
struct BtlObjNode *BtlObjListMoveHeadToTail(void)
{
    struct BtlObjNode *n = *(struct BtlObjNode **)gData_030040A8;
    struct BtlObjNode *t;

    if (n != 0)
    {
        *(struct BtlObjNode **)gData_030040A8 = n->prev;
        t = *(struct BtlObjNode **)gData_030040B8;
        if (t != 0)
            t->next = n;
        n->prev = *(struct BtlObjNode **)gData_030040B8;
        n->next = 0;
        *(struct BtlObjNode **)gData_030040B8 = n;
    }
    return n;
}

/* fn: sub_0806FF28 */
// @ 0x0806ff28
/* match-flags: -fprologue-bugfix */
void BtlObjListMoveToHead(struct BtlObj *a)
{
  struct BtlObj *r3;
  u32 r0;
  struct BtlObjNode *r2;
  struct BtlObjNode *r1;
  u32 loc;
  struct BtlObjNode **new_var;
  r3 = a;
  r0 = r3->unk19;
  if (r0 == 0)
  {
    r2 = r3->next;
    r1 = r3->prev;
    if (r2 != 0)
    {
      r2->prev = r1;
    }
    else
    {
      r0 = (u32) ((struct BtlObjNode **) 0x030040B8);
      *((struct BtlObjNode **) r0) = r1;
    }
    if (r1 != 0)
    {
      r1->next = r2;
    }
    new_var = (struct BtlObjNode **) 0x030040A8;
    loc = (u32) new_var;
    ;
    r3->prev = (struct BtlObjNode *) (*((u32 *) loc));
    *((struct BtlObj **) loc) = r3;
  }
}

/* fn: sub_0807000C */
// @ 0x0807000c
// Allocate `count` linked battle-object pool nodes tagged with `key` from the
// free list and splice the chain into the active list after the key's run.
struct Unk6FDB4 *BtlObjPoolAllocChain(struct SpriteChain *hdr, u16 count, u16 key)
{
    struct Unk6FDB4 *head;
    struct Unk6FDB4 *cur;
    struct Unk6FDB4 *prev;
    struct Unk6FDB4 *after;

    if (gData_030040B4 < count)
    {
        DebugPrint((void *)0x083D2244, gData_030040B4, count);
        return 0;
    }
    gData_030040B4 -= count;
    head = gData_030040AC;
    cur = head;
    after = BtlObjListFindInsertPoint(gData_030040A4, key);
    prev = head;
    hdr->count = count;
    hdr->head = head;
    head->unk22 = key;
    while (--count != 0)
    {
        cur = cur->unk04;
        cur->unk22 = key;
        cur->unk00 = prev;
        prev = cur;
    }
    hdr->tail = cur;
    gData_030040AC = cur->unk04;
    if (after == 0)
    {
        if (gData_030040A4 != 0)
            gData_030040A4->unk00 = cur;
        cur->unk04 = gData_030040A4;
        head->unk00 = after;
        gData_030040A4 = head;
    }
    else
    {
        if (after->unk04 != 0)
            after->unk04->unk00 = cur;
        cur->unk04 = after->unk04;
        head->unk00 = after;
        after->unk04 = head;
    }
    LinkedListValidate((struct Unk6F8C4 *)gData_030040A4);
    return head;
}

/* fn: sub_080700CC */
// @ 0x080700cc
// Release a pending battle-object batch: return its nodes to the free list,
// unlink the run from the active list and clear the batch header.
void BtlObjPoolReleaseChain(void *a)
{
    struct SpriteChain *batch;
    struct Unk700CCNode *node;
    struct Unk700CCNode *head;
    struct Unk700CCNode *tail;
    struct Unk700CCNode *prev;
    struct Unk700CCNode *next;
    u32 count;
    u32 i;

    batch = a;
    count = batch->count;
    if (count == 0)
        return;
    head = (struct Unk700CCNode *)batch->head;
    tail = (struct Unk700CCNode *)batch->tail;
    prev = head->unk00;
    next = tail->unk04;
    gData_030040B4 += count;
    node = head;
    i = count;
    while (i-- != 0)
    {
        if (node->unk30 != 0)
        {
            BtlObjListMoveToHead(node->unk30);
            node->unk30 = 0;
        }
        if (node->unk24 >= 0)
            VramSpanFree(node->unk24, 1 << (node->unk16 - 5));
        node->unk24 = -1;
        node = node->unk04;
    }

    if (prev != 0)
        prev->unk04 = next;
    else
        gData_030040A4 = (struct Unk6FDB4 *)next;
    if (next != 0)
        next->unk00 = prev;
    tail->unk04 = (struct Unk700CCNode *)gData_030040AC;
    gData_030040AC = (struct Unk6FDB4 *)head;
    batch->count = 0;
    batch->head = 0;
    batch->tail = 0;
    LinkedListValidate((struct Unk6F8C4 *)gData_030040A4);
}

/* fn: sub_08070188 */
// @ 0x08070188
/* match-compiler: old_agbcc */
// Resize a battle-object batch to count nodes: grow it in place from the free
// list (new nodes inherit the batch's key), allocate it fresh if it is empty,
// or release and reallocate it when shrinking. Returns the batch head.
struct Unk6FDB4 *BtlObjPoolResizeChain(struct SpriteChain *hdr, u16 count, u16 key)
{
    struct Unk6FDB4 *head;
    struct Unk6FDB4 *tail;
    struct Unk6FDB4 *cur;
    struct Unk6FDB4 *prev;
    u32 avail;

    if (hdr->count == count)
        return hdr->head;
    if (hdr->count < count)
    {
        if (hdr->count != 0)
        {
            count -= hdr->count;
            avail = gData_030040B4;
            if (avail < count)
            {
                DebugMessage((void *)0x083D2288);
                return NULL;
            }
            head = gData_030040AC;
            cur = head;
            tail = hdr->tail;
            prev = head;
            key = hdr->head->unk22;
            gData_030040B4 = avail - count;
            hdr->count += count;
            head->unk22 = key;
            while (--count != 0)
            {
                cur = cur->unk04;
                cur->unk22 = key;
                cur->unk00 = prev;
                prev = cur;
            }
            gData_030040AC = cur->unk04;
            if (tail->unk04 != NULL)
                tail->unk04->unk00 = cur;
            cur->unk04 = tail->unk04;
            tail->unk04 = head;
            head->unk00 = tail;
            hdr->tail = cur;
            LinkedListValidate((struct Unk6F8C4 *)gData_030040A4);
            return hdr->head;
        }
        BtlObjPoolAllocChain(hdr, count, key);
        return hdr->head;
    }
    DebugMessage((void *)0x083D22A4);
    BtlObjPoolReleaseChain(hdr);
    return BtlObjPoolAllocChain(hdr, count, key);
}

/* fn: sub_0807027C */
// @ 0x0807027c
// Set an object's scale (b, c) and rotation d, rebuilding its 2x2 affine
// matrix. A NULL obj takes one from the battle-object pool; the identity
// transform (d 0, scale 0x100) releases it instead. Busy objects (unk19) are
// left alone and their unk19 is returned.
struct AffineObj *BtlObjSetAffine(struct AffineObj *obj, u16 b, u16 c, u8 d)
{
    bool32 reset;
    s32 cos, sin, sx, sy;

    reset = FALSE;
    if (d == 0 && b == 0x100 && c == b)
        reset = TRUE;
    if (obj != NULL)
    {
        if (obj->locked != 0)
            return (struct AffineObj *)(u32)obj->locked;
        if (reset)
        {
            BtlObjListMoveToHead((struct BtlObj *)obj);
            return NULL;
        }
    }
    else
    {
        if (reset)
            return NULL;
        obj = (struct AffineObj *)BtlObjListMoveHeadToTail();
        if (obj == NULL)
            return NULL;
    }
    obj->scaleX = b;
    obj->scaleY = c;
    obj->angle = d;
    if (d != 0)
    {
        cos = gData_083C9544[d + 0x40];
        sx = gData_083A9544[b];
        obj->pa = (cos * sx) >> 8;
        sin = gData_083C9544[d];
        obj->pb = (sin * sx) >> 8;
        sin = -sin;
        sy = gData_083A9544[c];
        obj->pc = (sin * sy) >> 8;
        obj->pd = (cos * sy) >> 8;
    }
    else
    {
        obj->pa = gData_083A9544[b];
        obj->pb = d;
        obj->pc = d;
        obj->pd = gData_083A9544[c];
    }
    return obj;
}

/* fn: sub_08070468 */
// @ 0x08070468
/* Move a node to its sorted position in the gData_030040A4 list after its key changes. */
void BtlObjListResort(struct Unk6FDB4 *node, u16 key)
{
    struct Unk6FDB4 *found;

    if (node->unk22 == key)
        return;
    if (node->unk00 != NULL)
        node->unk00->unk04 = node->unk04;
    else
        gData_030040A4 = node->unk04;
    if (node->unk04 != NULL)
        node->unk04->unk00 = node->unk00;
    node->unk22 = key;
    found = BtlObjListFindInsertPoint(gData_030040A4, key);
    if (found == NULL)
    {
        if (gData_030040A4 != NULL)
            gData_030040A4->unk00 = node;
        node->unk04 = gData_030040A4;
        node->unk00 = found;
        gData_030040A4 = node;
    }
    else
    {
        if (found->unk04 != NULL)
            found->unk04->unk00 = node;
        node->unk04 = found->unk04;
        node->unk00 = found;
        found->unk04 = node;
    }
}
