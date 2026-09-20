#include "global.h"

// @ 0x0807179c
void sub_0807179C(struct Unk7179C *arg0)
{
    s32 count;
    struct Unk7179CNode *a;
    struct Unk7179CNode *b;
    s32 i;
    struct Unk7179CNode tmp;

    count = arg0->unk1C - 1;
    a = arg0->unk14;
    b = arg0->unk18;
    i = 0;
    if (count <= 0)
        goto done;
loop:
    _08075A58(&tmp, a, 0x34);
    a->unk08 = b->unk08;
    a->unk0C = b->unk0C;
    a->unk18 = b->unk18;
    a->unk24 = b->unk24;
    b->unk08 = tmp.unk08;
    b->unk0C = tmp.unk0C;
    b->unk18 = tmp.unk18;
    b->unk24 = tmp.unk24;
    i++;
    count--;
    a = a->unk04;
    b = b->unk00;
    if (count > i)
        goto loop;
done:
    return;
}

