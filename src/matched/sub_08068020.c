#include "global.h"

// @ 0x08068020

void AnimObjSelectSeq(struct AnimObjSeqSelect *a, u16 key, u16 arg2)
{
    struct AnimData *inner;
    struct AnimSeqEntry *rec;
    u32 i;
    u32 off;
    u32 acc;

    acc = 0;
    inner = a->data;
    rec = (struct AnimSeqEntry *)((u8 *)inner + inner->seqTableOffset);
    i = 0;
    while (i < a->seqCount)
    {
        if (rec->key == key)
        {
            a->seqOffset = acc;
            a->seqStep = 0;
            a->seqKey = key;
            a->seqNextKey = arg2;
            AnimObjSetRecord((struct AnimObjPlayback *)a, rec->firstRecord);
            return;
        }
        off = rec->size;
        rec = (struct AnimSeqEntry *)((u8 *)rec + off);
        acc = (u16)(acc + off);
        i++;
    }
}

