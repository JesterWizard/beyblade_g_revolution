/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void sub_08068598(struct Unk68598 *work)
{
    struct Unk68598Record *record;
    struct Unk68598Lookup *lookup;
    u16 delay;
    s32 total;
    s32 last;
    u16 start;
    u16 length;

    record = (struct Unk68598Record *)&work->unk00->unk20[work->unk20];
    if ((work->unk98 & 4) != 0
        || (lookup = (struct Unk68598Lookup *)((u8 *)work->unk00 + work->unk00->unk08 * 8 + 0x20),
            (u8 *)lookup == (u8 *)work->unk00 + work->unk00->unk18))
        lookup = NULL;
    total = work->unk34 + work->unk36;
    if (lookup != NULL)
        delay = total + *(u16 *)((u8 *)lookup + work->unk22 * 2 + 2);
    else
        delay = total;
    if (delay < gUnk_03000180.unk08)
        delay = gUnk_03000180.unk08;
    if (gUnk_03000180.unk00 - work->unk58 < delay)
        return;
    work->unk58 += delay;
    start = record->value;
    length = record->unk02;
    work->unk60 = work->unk22;
    if (work->unk33 & 2)
        work->unk22--;
    else
        work->unk22++;
    if (work->unk22 > (last = start - 1) + length)
    {
        if (work->unk33 & 1)
        {
            work->unk33 ^= 2;
            work->unk22 = start + (length - 2);
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
            work->unk22 = start + (length - 1);
        }
        work->unk24++;
    }
    if (work->unk32 != 0 && work->unk24 >= work->unk32)
        sub_08068118((struct Unk68118 *)work);

}

