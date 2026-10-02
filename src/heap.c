#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_08041394 */
// @ 0x08041394
void HeapFreeSlots8(struct Unk41394 *a)
{
    s32 i;
    void *q;

    i = 0;
    do
    {
        q = a->unk220[i];
        if (q != 0)
        {
            HeapFree(q);
            a->unk220[i] = 0;
        }
        i++;
    } while (i <= 7);
}

/* fn: sub_08062728 */
// @ 0x08062728
/* match-compiler: old_agbcc */
// Zero `a->unk08` words starting at `a->unk04` (a do-while, so a zero count still
// writes one word -- matching retail, which has no entry guard).
// The zero must be its own local, initialised AFTER `i` but BEFORE the count and
// pointer: agbcc hoists `movs r3,#0` out of the loop, and only this declaration
// order makes it come before the two ldr's (`0021 0023 8268 4068` in retail).
// With the zero written inline (`*p++ = 0`) the mov lands after the loads (13/18),
// and with the zero declared first the two movs swap (16/18).
void BufferClearWords(struct Unk62728 *a)
{
    u32 i = 0;
    u32 z = 0;
    u32 n = a->unk08;
    u32 *p = a->unk04;

    do
    {
        *p++ = z;
        i++;
    } while (i < n);
}

/* fn: sub_0806A314 */
// @ 0x0806a314
/* match-compiler: old_agbcc */

void *FastAllocate(struct Unk6A314 *state)
{
    struct Unk6A4D8Node *node;
    void *buffer;
    void **current;
    u32 current_value;
    s32 *payload;
    s32 *next_payload;
    u32 pool;
    u32 neg;

    current = &gUnk_03003F44;
    current_value = (u32)*current;
    pool = 0x03003F40;
    if (current_value == 0)
    {
        *current = *(void **)pool;
        gUnk_03003F48 = current_value;
        buffer = (void *)0x03000B40;
        *(u32 *)0x03000B40 = *(u32 *)buffer;
        gUnk_03003F4C = current_value;
    }
    buffer = GetValidAllocatedBlock(*(void **)pool, 0x20);
    if (buffer == 0)
        DebugPrint((void *)0x083D1AC8, state);
    node = HeapRegionInsert(
        (u32)state + 8,
        (void *)0x03000B40,
        0xD0 << 6,
        *current,
        buffer,
        (struct Unk6A4D8Node **)current);
    if (node != 0)
    {
        gUnk_03003F48++;
        node->unk04 -= 8;
        payload = node->unk00;
        next_payload = payload + 1;
        node->unk00 = next_payload;
        neg = 1;
        neg = -neg;
        *payload = (s32)neg;
        next_payload = (s32 *)((u32)next_payload + node->unk04);
        *next_payload = (s32)neg;
    }
    return node;
}

/* fn: sub_0806A3A4 */
// @ 0x0806a3a4
/* match-compiler: old_agbcc */
void *HeapAlloc(u32 size)
{
    struct Unk6A4D8Node *node;
    void *buffer;
    void **current;
    u32 current_value;
    s32 *payload;
    s32 *next_payload;
    u32 pool;
    u32 neg;

    current = &gUnk_03000B30;
    current_value = (u32)*current;
    pool = 0x03003F50;
    if (current_value == 0)
    {
        *current = *(void **)pool;
        gUnk_03000B3C = current_value;
        buffer = (void *)0x03000B34;
        gUnk_03000B34 = *(u32 *)buffer;
        gUnk_03000B38 = current_value;
    }
    buffer = GetValidAllocatedBlock(*(void **)pool, 0x60);
    if (buffer == 0)
        DebugPrint((void *)0x083D1B00, (void *)size);
    node = HeapRegionInsert(
        size + 8,
        (void *)gUnk_03000B34,
        0xFE << 10,
        *current,
        buffer,
        (struct Unk6A4D8Node **)current);
    if (node != 0)
    {
        gUnk_03000B3C++;
        node->unk04 -= 8;
        payload = node->unk00;
        next_payload = payload + 1;
        node->unk00 = next_payload;
        neg = 1;
        neg = -neg;
        *payload = (s32)neg;
        next_payload = (s32 *)((u32)next_payload + node->unk04);
        *next_payload = (s32)neg;
    }
    return node;
}

/* fn: sub_0806A434 */
// @ 0x0806a434
void HeapFree(void *arg)
{
    struct Unk6A434 *state;
    struct Unk6A4D8Node *previous;
    struct Unk6A4D8Node *next;

    state = arg;
    previous = state->unk0C;
    next = state->unk08;
    if (state->unk00 == 0)
        DebugPrint((void *)0x083D1B38);
    if (next == 0)
    {
        if (previous == 0)
        {
            if (state->unk00 <= 0x0203FFFF)
                gUnk_03000B30 = previous;
            else
                gUnk_03003F44 = previous;
        }
        else
        {
            if (state->unk00 <= 0x0203FFFF)
                gUnk_03000B30 = previous;
            else
                gUnk_03003F44 = previous;
            if (previous != 0)
                previous->unk08 = 0;
        }
    }
    else
    {
        next->unk0C = previous;
        if (previous != 0)
            previous->unk08 = next;
    }
    if (state->unk00 <= 0x0203FFFF)
        gUnk_03000B3C--;
    else
        gUnk_03003F48--;
    state->unk04 = 0;
    state->unk00 = 0;
    state->unk0C = 0;
    state->unk08 = 0;
}

/* fn: sub_0806A4D8 */
// @ 0x0806a4d8
/* First-fit insert of an `size`-byte block into the sorted region list at `head`. */
void *HeapRegionInsert(u32 size, u8 *start, u32 len, struct Unk6A4D8Node *head, struct Unk6A4D8Node *out, struct Unk6A4D8Node **outp)
{
    struct Unk6A4D8Node *walk;
    struct Unk6A4D8Node *next;
    u8 *end;
    u8 *pos;
    u32 room;
    u32 gap;

    if (head->unk00 != NULL)
        gap = (u8 *)head->unk00 - start;
    else
        gap = 0;
    if (gap >= size)
    {
        out->unk00 = (s32 *)start;
        out->unk08 = NULL;
        out->unk0C = head;
        out->unk04 = size;
        head->unk08 = out;
        *outp = out;
        return out;
    }
    walk = head;
    if (walk != NULL)
    {
        do
        {
            next = walk->unk0C;
            if (next != NULL)
            {
                end = (u8 *)walk->unk00 + walk->unk04;
                if ((u32)((u8 *)next->unk00 - end) >= size)
                {
                    out->unk00 = (s32 *)end;
                    out->unk08 = walk;
                    out->unk0C = walk->unk0C;
                    out->unk04 = size;
                    walk->unk0C->unk08 = out;
                    walk->unk0C = out;
                    return out;
                }
                walk = next;
            }
            else if (walk->unk00 != NULL)
            {
                pos = (u8 *)walk->unk00 + walk->unk04;
                room = start + len - pos;
            }
            else
            {
                pos = start;
                room = len;
            }
        } while (next != NULL);
    }
    if (room >= size)
    {
        out->unk00 = (s32 *)pos;
        out->unk04 = size;
        out->unk0C = NULL;
        if (out == walk)
        {
            out->unk08 = NULL;
        }
        else
        {
            out->unk08 = walk;
            walk->unk0C = out;
        }
        return out;
    }
    return NULL;
}

/* fn: sub_0806A580 */
// @ 0x0806a580
void *GetValidAllocatedBlock(struct Unk6A580 *p, u32 n)
{
    u32 t;

    while (1)
    {
        t = n;
        n--;
        if (t == 0)
            break;
        if (p->unk04 == 0)
        {
            if (p->unk00 == 0)
                return p;
        }
        p++;
    }
    DebugPrint((void *)0x083D1B5C, n);
    return 0;
}

/* fn: sub_0806F8C4 */
// @ 0x0806f8c4
void LinkedListValidate(struct Unk6F8C4 *a)
{
    struct Unk6F8C4 *p;
    struct Unk6F8C4 *n;

    p = a;
    if (p == 0)
        return;
    n = p->unk00;
    if (n != 0)
        DebugPrint((void *)0x083D2074);
    do
    {
        if (n != 0)
        {
            if (n->unk04 != p)
                DebugPrint((void *)0x083D2090);
        }
        if (p->unk00 != n)
            DebugPrint((void *)0x083D20AC);
        n = p;
        p = p->unk04;
    } while (p != 0);
}

/* fn: sub_08073184 */
// @ 0x08073184
void MemClear(u8 *a, u32 n)
{
    u32 i;

    if (a != 0 && n != 0)
    {
        i = 0;
        while (i < n)
        {
            a[i] = 0;
            i++;
        }
    }
}
