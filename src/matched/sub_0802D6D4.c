#include "global.h"

// @ 0x0802d6d4
void sub_0802D6D4(void)
{
    struct Unk705DC *resource;
    struct Unk026C *w;

    resource = sub_0806FDD0(2);
    gUnk_0300026C->unk08 = resource;
    sub_0806FF58(
        resource, (void *)0x080D63CC,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    sub_080705DC(gUnk_0300026C->unk08, 2);

    gUnk_0300026C->unk0C = sub_0806FDD0(0);
    gUnk_0300026C->unk10 = sub_0806FDD0(0);
    gUnk_0300026C->unk14 = sub_0806FDD0(0);
    gUnk_0300026C->unk18 = sub_0806FDD0(0);
    gUnk_0300026C->unk1C = sub_0806FDD0(0);
    gUnk_0300026C->unk20 = sub_0806FDD0(0);
    gUnk_0300026C->unk24 = sub_0806FDD0(0);

    sub_0806FF58(
        gUnk_0300026C->unk0C, (void *)0x08266DAC,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    sub_0806FF58(
        gUnk_0300026C->unk10, (void *)0x080D6618,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0,
        gMainWorkPtr->unk1818);
    sub_0806FF58(
        gUnk_0300026C->unk14, (void *)0x080D6B68,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    sub_0806FF58(
        gUnk_0300026C->unk18, (void *)0x080D6B68,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    sub_0806FF58(
        gUnk_0300026C->unk1C, (void *)0x080D6B68,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    sub_0806FF58(
        gUnk_0300026C->unk20, (void *)0x080D6B68,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    sub_0806FF58(
        gUnk_0300026C->unk24, (void *)0x080D6D50,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);

    sub_080705DC(gUnk_0300026C->unk0C, 2);
    sub_080705DC(gUnk_0300026C->unk10, 2);
    sub_080705DC(gUnk_0300026C->unk14, 2);
    sub_080705DC(gUnk_0300026C->unk18, 2);
    sub_080705DC(gUnk_0300026C->unk1C, 2);
    sub_080705DC(gUnk_0300026C->unk20, 2);
    sub_080705DC(gUnk_0300026C->unk24, 2);

    w = gUnk_0300026C;
    w->unk00 = 0;
    w->unk4C = 0xFFFF;
    w->unk04 = 0;
    w->unk48 = 0xFF;
}

