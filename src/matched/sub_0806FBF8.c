#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806fbf8
/* match-compiler: old_agbcc */
// Return the span [start, start + size) to the sorted free list at
// gData_03004088: grow a neighbouring span when it touches one, otherwise link
// in a node taken from the spare list gData_03004098. Then coalesce adjacent
// spans, returning the absorbed nodes to the spare list.
void VramSpanFree(s32 start, s32 size)
{
    struct Unk6FBF8Span *cur;
    struct Unk6FBF8Span *spare;
    struct Unk6FBF8Span *prev;
    struct Unk6FBF8Span *next;
    s32 end;

    cur = gData_03004088;
    spare = gData_03004098;
    prev = NULL;
    end = start + size;
    while (cur != NULL)
    {
        if (end == cur->start)
        {
            cur->start -= size;
            cur->size += size;
            break;
        }
        if (start == cur->start + cur->size)
        {
            cur->size += size;
            break;
        }
        if (cur->start > start)
        {
            if (spare == NULL)
            {
                DebugPrint((void *)0x083D2184);
                return;
            }
            gData_03004098 = spare->next;
            if (prev != NULL)
                prev->next = spare;
            else
                gData_03004088 = spare;
            spare->next = cur;
            spare->start = start;
            spare->size = size;
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    cur = gData_03004088->next;
    prev = gData_03004088;
    while (cur != NULL)
    {
        if (cur->start == prev->start + prev->size)
        {
            next = cur->next;
            prev->size = cur->size + prev->size;
            prev->next = next;
            cur->next = gData_03004098;
            gData_03004098 = cur;
            cur = next;
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

