#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068598
/* match-compiler: old_agbcc */
// Advance an animation by one frame once its delay has elapsed: the delay is
// unk34 + unk36 plus the per-frame entry from the optional delay table, never
// below the global minimum. Steps unk22 forward or back (unk33 bit 1) within
// the current record's [start, start + len), wrapping or ping-ponging (bit 0),
// counting loops in unk24; calls sub_08068118 once that reaches unk32.
void AnimAdvanceFrame(struct AnimObjPlayback *work)
{
    struct AnimRecord *rec;
    struct Unk68598Lookup *lookup;
    s32 total;
    u16 delay;
    u16 start;
    u16 len;
    u32 off;
    struct Unk68598Lookup *end;
    s32 last;

    rec = &work->data->unk20[work->recIndex];
    if (!(work->flags & 4))
    {
        off = work->data->recordCount * 8 + 0x20;
        end = (struct Unk68598Lookup *)((u8 *)work->data + work->data->seqTableOffset);
        lookup = (struct Unk68598Lookup *)((u8 *)work->data + off);
        if (lookup == end)
            lookup = NULL;
    }
    else
        lookup = NULL;
    total = work->frameDelay + work->delayBonus;
    delay = lookup != NULL ? (&lookup->unk00)[work->frame + 1] + total : total;
    if (delay < gData_03000180.unk08)
        delay = gData_03000180.unk08;
    if (gData_03000180.unk00 - work->lastAdvanceTick < delay)
        return;
    work->lastAdvanceTick += delay;
    start = rec->start;
    len = rec->length;
    work->prevFrame = work->frame;
    if (work->playFlags & 2)
        work->frame--;
    else
        work->frame++;
    if (work->frame > (last = start - 1) + len)
    {
        if (work->playFlags & 1)
        {
            work->playFlags ^= 2;
            work->frame = start + (len - 2);
        }
        else
        {
            work->frame = start;
        }
        work->loopCount++;
    }
    if (work->frame < start)
    {
        if (work->playFlags & 1)
        {
            work->playFlags ^= 2;
            work->frame = start + 1;
        }
        else
        {
            work->frame = start + (len - 1);
        }
        work->loopCount++;
    }
    if (work->maxLoops != 0 && work->loopCount >= work->maxLoops)
        AnimObjSeqAdvance((struct AnimObjSeqStep *)work);
}

