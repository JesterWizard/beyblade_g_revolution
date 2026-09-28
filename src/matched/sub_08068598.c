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
void AnimAdvanceFrame(struct Unk68598 *work)
{
    struct Unk68014Rec *rec;
    struct Unk68598Lookup *lookup;
    s32 total;
    u16 delay;
    u16 start;
    u16 len;
    u32 off;
    struct Unk68598Lookup *end;
    s32 last;

    rec = &work->unk00->unk20[work->unk20];
    if (!(work->unk98 & 4))
    {
        off = work->unk00->unk08 * 8 + 0x20;
        end = (struct Unk68598Lookup *)((u8 *)work->unk00 + work->unk00->unk18);
        lookup = (struct Unk68598Lookup *)((u8 *)work->unk00 + off);
        if (lookup == end)
            lookup = NULL;
    }
    else
        lookup = NULL;
    total = work->unk34 + work->unk36;
    delay = lookup != NULL ? (&lookup->unk00)[work->unk22 + 1] + total : total;
    if (delay < gData_03000180.unk08)
        delay = gData_03000180.unk08;
    if (gData_03000180.unk00 - work->unk58 < delay)
        return;
    work->unk58 += delay;
    start = rec->unk00;
    len = rec->unk02;
    work->unk60 = work->unk22;
    if (work->unk33 & 2)
        work->unk22--;
    else
        work->unk22++;
    if (work->unk22 > (last = start - 1) + len)
    {
        if (work->unk33 & 1)
        {
            work->unk33 ^= 2;
            work->unk22 = start + (len - 2);
        }
        else
        {
            work->unk22 = start;
        }
        work->unk24++;
    }
    if (work->unk22 < start)
    {
        if (work->unk33 & 1)
        {
            work->unk33 ^= 2;
            work->unk22 = start + 1;
        }
        else
        {
            work->unk22 = start + (len - 1);
        }
        work->unk24++;
    }
    if (work->unk32 != 0 && work->unk24 >= work->unk32)
        sub_08068118((struct Unk68118 *)work);
}

