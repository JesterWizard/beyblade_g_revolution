#include "global.h"

void sub_0802DEA0(void)
{
    struct Unk026C *p = gUnk_0300026C;

    if (p->unk0C != 0)
    {
        p->unk0C->unk08 = 0xFFFFC000;
        p->unk0C->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk10 != 0)
    {
        p->unk10->unk08 = 0xFFFFC000;
        p->unk10->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk14 != 0)
    {
        p->unk14->unk08 = 0xFFFFC000;
        p->unk14->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk18 != 0)
    {
        p->unk18->unk08 = 0xFFFFC000;
        p->unk18->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk1C != 0)
    {
        p->unk1C->unk08 = 0xFFFFC000;
        p->unk1C->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk20 != 0)
    {
        p->unk20->unk08 = 0xFFFFC000;
        p->unk20->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk24 != 0)
    {
        p->unk24->unk08 = 0xFFFFC000;
        p->unk24->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk28 != 0)
    {
        p->unk28->unk08 = 0xF800;
        p->unk28->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->unk2C != 0)
    {
        p->unk2C->unk08 = 0xF800;
        p->unk2C->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->unk40 != 0)
    {
        p->unk40->unk08 = 0xF800;
        p->unk40->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->unk30 != 0)
    {
        p->unk30->unk08 = 0xF800;
        p->unk30->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->unk34 != 0)
    {
        p->unk34->unk08 = 0xF800;
        p->unk34->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->unk38 != 0)
    {
        p->unk38->unk08 = 0xF800;
        p->unk38->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->unk3C != 0)
    {
        p->unk3C->unk08 = 0xF800;
        p->unk3C->unk0C = 0xF800;
    }

    p = gUnk_0300026C;
    if (p->unk28 != 0)
    {
        sub_0806FE84(p->unk28);
        gUnk_0300026C->unk28 = 0;
    }
    p = gUnk_0300026C;
    if (p->unk2C != 0)
    {
        sub_0806FE84(p->unk2C);
        gUnk_0300026C->unk2C = 0;
    }
    p = gUnk_0300026C;
    if (p->unk30 != 0)
    {
        sub_0806FE84(p->unk30);
        gUnk_0300026C->unk30 = 0;
    }
    p = gUnk_0300026C;
    if (p->unk34 != 0)
    {
        sub_0806FE84(p->unk34);
        gUnk_0300026C->unk34 = 0;
    }
    p = gUnk_0300026C;
    if (p->unk38 != 0)
    {
        sub_0806FE84(p->unk38);
        gUnk_0300026C->unk38 = 0;
    }
    p = gUnk_0300026C;
    if (p->unk3C != 0)
    {
        sub_0806FE84(p->unk3C);
        gUnk_0300026C->unk3C = 0;
    }
    p = gUnk_0300026C;
    if (p->unk40 != 0)
    {
        sub_0806FE84(p->unk40);
        gUnk_0300026C->unk40 = 0;
    }

    sub_080674B4();
    _08073C40(*(void **)0x080BB888);

    gUnk_0300026C->unk48 = 0xFF;
    gMainWorkPtr->unk1838 |= 0xFFFF;
    gMainWorkPtr->unk183A |= 0xFFFF;
}
