#include "global.h"

// @ 0x08068020

void sub_08068020(struct Unk680CC *a, u16 key, u16 arg2)
{
    struct Unk68014 *inner;
    struct Unk680CCRec *rec;
    u32 i;
    u32 off;
    u32 acc;

    acc = 0;
    inner = a->unk00;
    rec = (struct Unk680CCRec *)((u8 *)inner + inner->unk18);
    i = 0;
    while (i < a->unk28)
    {
        if (rec->unk00 == key)
        {
            a->unk1C = acc;
            a->unk1E = 0;
            a->unk1A = key;
            a->unk2E = arg2;
            sub_08068180((struct Unk68598 *)a, rec->unk08);
            return;
        }
        off = rec->unk02;
        rec = (struct Unk680CCRec *)((u8 *)rec + off);
        acc = (u16)(acc + off);
        i++;
    }
}

