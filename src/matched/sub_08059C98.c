#include "global.h"

// @ 0x08059c98
void *sub_08059C98(struct Unk59C98Src *src, struct Unk59C98Owner *owner, void *a2, void *a3)
{
    struct Unk59C6C *p;
    s32 i;
    void *q;
    void *tmp;

    p = *(struct Unk59C6C **)gUnk_03000730;
    i = 0;
    if (p == 0)
        return 0;
    do
    {
        tmp = p->unk00;
        if (tmp == 0)
        {
            p->unk00 = src->unk00;
            p->unk04 = src->unk04;
            p->unk08 = src->unk08;
            p->unk18 = src->unk10;
            p->unk1C = src->unk14;
            p->unk20 = src->unk18;
            p->unk24 = src->unk1C;
            p->unk28 = src->unk20;
            p->unk38 = owner;
            p->unk34 = tmp;
            p->unk2C = a2;
            p->unk30 = a3;
            p->unk14 = 1;
            owner->unkC8 = p;
            if (src->unk0C != 0)
            {
                q = BtlObjAlloc(src->unk0C);
                p->unk0C = q;
                p->unk10 = *(void **)q;
            }
            return p;
        }
        p++;
        i++;
    } while (i <= 0x13);
    return 0;
}

