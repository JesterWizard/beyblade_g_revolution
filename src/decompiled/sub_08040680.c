#include "global.h"
#include "ram_map.h"

void sub_08040680(struct Unk40680 *a)
{
    s32 i;
    s32 value;
    u32 d;
    u16 y;
    u16 f;

    if (a->unk274 != NULL)
    {
        sub_0806FE84(a->unk274);
        a->unk274 = NULL;
    }
    for (i = 0; i <= 8; i++)
        MemClear(gUnk_0300047C->unk810[i], 0x60);
    value = sub_08040618();
    gUnk_0300047C->unk834 = BtlObjTableAdd(0x400);
    _080408E4(value);
    TextSetActiveObject((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    d = sub_08061A98();
    y = sub_08061784() - 0x28;
    f = sub_08061AA8();
    a->unk2FC = sub_080737C0(gUnk_0300047C->unk810, gUnk_0300047C->unk834, 9, d, y, f, sub_080617B4(), 0x60);
    BtlObjTableRemove(gUnk_0300047C->unk834);
    a->unk300 = 0;
    sub_08061BDC((struct Unk61BDC *)a->unk220->unk00);
    sub_08061BE8();
    sub_08061E40((struct Unk61E40 *)a->unk220->unk00);
    if (gMainWorkPtr->unk184F != 0)
        *(u32 *)0x03000474 = 1;
    else
        *(u32 *)0x03000474 = 2;
}
