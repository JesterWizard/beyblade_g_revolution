#include "global.h"

// @ 0x080726a4
void sub_080726A4(struct Unk726A4 *a, s32 b, s32 c, s32 d, s32 e)
{
    c &= ~1;
    d &= ~1;
    a->unk10 = HeapAlloc((d << 1) * e);
    a->unk04 = c;
    a->unk06 = d;
    a->unk08 = e;
    a->unk00 = b;
    a->unk0C = *a->unk10;
}
