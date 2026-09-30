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
        BtlObjPoolFree(a->unk274);
        a->unk274 = NULL;
    }
    for (i = 0; i <= 8; i++)
        MemClear(gUnk_0300047C->unk810[i], 0x60);
    value = sub_08040618();
    {
        u8 *buf = StringAlloc(0x400);
        gUnk_0300047C->unk834 = buf;
        _080408E4(value, buf);
    }
    TextSetActiveObject((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    d = TextGetWidthTable();
    y = TextGetAreaWidth() - 0x28;
    f = TextGetGlyphWidth();
    a->unk2FC = SplitStringIntoStringArray(gUnk_0300047C->unk810, gUnk_0300047C->unk834, 9, d, y, f, TextGetSpacing(), 0x60);
    StringFree(gUnk_0300047C->unk834);
    a->unk300 = 0;
    TextTypewriterResume((struct Unk61BDC *)a->unk220->unk00);
    TextWindowPopState();
    TextTypewriterRestart((struct Unk61E40 *)a->unk220->unk00);
    if (gMainWorkPtr->unk184F != 0)
        *(u32 *)0x03000474 = 1;
    else
        *(u32 *)0x03000474 = 2;
}
