#include "global.h"

// @ 0x08071e04
void SoundChannelInit(struct SoundChannel *p, void *a, u32 n)
{
    p->state = 1;
    p->data = (s32)a;
    p->unk14 = 0;
    p->unk17 = 0;
    p->volume = 0x100;
    p->cursor = (s32)((u8 *)a + 0x10);
    if (n > 0x7F)
        n = 0x7F;
    p->rate = (s32)(*(void ***)gUnk_030000C4)[n];
    p->unk0C = 0;
    p->list = 0;
    p->listIndex = 0;
    p->unk24 = 0;
}

