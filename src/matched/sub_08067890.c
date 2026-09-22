#include "global.h"

// @ 0x08067890

void TimerAdvance(void)
{
    struct Unk0180 *p;

    p = &gUnk_03000180;
    p->unk04 = p->unk00;
    p->unk00 = p->unk00 + p->unk08;
}

