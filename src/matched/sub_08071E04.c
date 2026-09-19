#include "global.h"

// @ 0x08071e04
void sub_08071E04(struct Unk71E84 *p, void *a, u32 n)
{
    p->unk16 = 1;
    p->unk00 = (s32)a;
    p->unk14 = 0;
    p->unk17 = 0;
    p->unk10 = 0x100;
    p->unk04 = (s32)((u8 *)a + 0x10);
    if (n > 0x7F)
        n = 0x7F;
    p->unk08 = (s32)(*(void ***)gUnk_030000C4)[n];
    p->unk0C = 0;
    p->unk1C = 0;
    p->unk20 = 0;
    p->unk24 = 0;
}

