#include "global.h"

// @ 0x08044ee8
void BtlClearUnk1688Entry(s32 idx)
{
    struct Unk1688Entry *p;

    p = &gMainWorkPtr->unk1688[idx];
    p->unk04 = 0;
    p->unk00 = 0;
    p->unk08 = 0;
    p->unk10 = 0;
    p->unk12 = 0;
    p->unk14 = 0;
    p->unk16 = 0;
}

