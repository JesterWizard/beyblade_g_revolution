#include "global.h"

struct Unk680CCRec *sub_08067F98(struct Unk680CC *a, u16 key)
{
    struct Unk68014 *inner;
    struct Unk680CCRec *rec;
    u16 count;
    s32 i;

    inner = a->unk00;
    rec = (struct Unk680CCRec *)((u8 *)inner + inner->unk18);
    i = 0;
    count = a->unk28;

    for (; i < count; i++)
    {
        if (rec->unk00 == key)
            return rec;
        rec = (struct Unk680CCRec *)((u8 *)rec + rec->unk02);
    }

    return 0;
}
