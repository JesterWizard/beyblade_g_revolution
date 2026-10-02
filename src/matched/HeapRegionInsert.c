#include "global.h"
#include "ram_map.h"
#include "battle.h"

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
