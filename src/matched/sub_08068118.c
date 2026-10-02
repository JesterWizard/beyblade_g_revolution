#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068118
/* match-compiler: old_agbcc */
void AnimObjSeqAdvance(struct AnimObjSeqStep *a)
{
    struct Unk68118Table *table;
    u16 next;
    s32 arg;

    table = (struct Unk68118Table *)((u8 *)a->data + a->data->seqTableOffset + a->seqOffset);
    if (a->seqStep < table->unk04 - 1)
    {
        next = a->seqStep + 1;
    }
    else
    {
        next = 0;
        if ((s16)a->seqNextKey != -1)
        {
            arg = a->seqKey;
            AnimObjSelectSeq((struct AnimObjSeqSelect *)a, a->seqNextKey, 0xFFFF);
            if (a->onFinish != NULL)
                _08073C48(a, (void *)arg, a->onFinish);
            return;
        }
    }
    a->seqStep = next;
    AnimObjSetRecord((struct AnimObjPlayback *)a, ((u16 *)table)[next + 4]);
}


