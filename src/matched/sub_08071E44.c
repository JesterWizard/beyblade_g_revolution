#include "global.h"

// @ 0x08071e44
void SoundChannelInitFromList(struct SoundChannel *p, void *a, s16 *idx)
{
    s32 val;
    s32 zero;
    s32 one;
    s32 offset;

    offset = *idx;
    offset = offset << 2;
    offset = offset + (s32)a;
    val = *(s32 *)offset;
    zero = 0;
    one = 1;
    p->state = one;
    p->data = val;
    p->unk14 = zero;
    p->unk17 = 0;
    p->volume = 0x100;
    val += 0x10;
    p->cursor = val;
    p->rate = **(s32 **)0x030000C4;
    p->unk0C = zero;
    p->list = a;
    p->listIndex = idx;
    p->unk24 = one;
}
