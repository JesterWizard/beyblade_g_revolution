#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080444bc
void sub_080444BC(void)
{
    struct Unk447CC *p;

    p = sub_08043B58();
    sub_08062AC0();
    if ((u32)gMainWorkPtr->unk036C == 0x083147C8)
        ObjPalLoadSlot(0, (void *)0x083002E0);
    else
        ObjPalLoadSlot(0, (void *)0x083006E0);
    ObjPalLoadSlot(1, (void *)0x082FDEE0);
    ObjPalLoadSlot(2, (void *)0x0826E320);
    if (p != NULL)
    {
        if (p->unk14 != NULL)
            sub_08059DC8(0, p->unk14);
        if (p->unk04 != NULL)
            sub_080447E8(p->unk04);
        if (p->unk08 != NULL)
            sub_08044648(p->unk08);
        if (p->unk0C != NULL)
            sub_08062A1C((u32)p->unk0C);
        if (p->unk10 != NULL)
            sub_080447B4(p->unk10);
        gMainWorkPtr->unk16E0 = p->unk1C;
        gMainWorkPtr->unk16E8 = p->unk20;
        gMainWorkPtr->unk16E4 = p->unk24;
        gMainWorkPtr->unk1825 = 0;
        if (p->unk28 & 1)
            gMainWorkPtr->unk1825 = 1;
        if (p->unk28 & 2)
            sub_0802DEA0();
        else
            sub_0802E048();
        if (p->unk28 & 4)
        {
            TextWindowOpenEx(gMainWorkPtr->unk15DC, (void *)0x082BCD00, (void *)0x080B738E, 0x1C0, 0x1C, 0x10, 1, 4, 0x0D, 2);
            sub_08069B78(gMainWorkPtr->unk1690->unk74_0, gMainWorkPtr->unk1690->unk74_2, 1, 0);
        }
    }
    else
    {
        gMainWorkPtr->unk16E0 = NULL;
        gMainWorkPtr->unk16E8 = NULL;
        gMainWorkPtr->unk16E4 = NULL;
        gMainWorkPtr->unk1825 = 0;
    }
    sub_0804495C();
}

