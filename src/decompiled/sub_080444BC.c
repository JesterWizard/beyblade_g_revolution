#include "global.h"

void sub_080444BC(void)
{
    struct Unk447CC *p;
    struct MainWork *main;
    u8 flags;

    p = sub_08043B58();
    sub_08062AC0();
    main = gMainWorkPtr;
    if ((u32)main->unk036C == 0x083147C8)
        ObjPalLoadSlot(0, (void *)0x083002E0);
    else
        ObjPalLoadSlot(0, (void *)0x083006E0);
    ObjPalLoadSlot(1, (void *)0x082FDEE0);
    ObjPalLoadSlot(2, (void *)0x0826E320);
    if (p == 0)
    {
        main->unk16E0 = 0;
        main->unk16E8 = 0;
        main->unk16E4 = 0;
        main->unk1825 = 0;
    }
    else
    {
        if (p->unk14 != 0)
            sub_08059DC8(0, p->unk14);
        if (p->unk04 != 0)
            sub_080447E8(p->unk04);
        if (p->unk08 != 0)
            sub_08044648(p->unk08);
        if (p->unk0C != 0)
            sub_08062A1C((u32)p->unk0C);
        if (p->unk10 != 0)
            sub_080447B4(p->unk10);
        main->unk16E0 = p->unk1C;
        main->unk16E8 = p->unk20;
        main->unk16E4 = p->unk24;
        main->unk1825 = 0;
        if ((p->unk28 & 1) != 0)
            main->unk1825 = 1;
        if ((p->unk28 & 2) != 0)
            sub_0802DEA0();
        else
            sub_0802E048();
        if ((p->unk28 & 4) != 0)
        {
            sub_08060C30(
                &main->unk15DC[0],
                (void *)0x082BCD00,
                (void *)0x080B738E,
                0x1C0,
                0x1C,
                0x10,
                1,
                6,
                0x0D,
                2);
            flags = main->unk1690->unk74;
            sub_08069B78(flags & 3, (flags >> 2) & 3, 1, 0);
        }
    }
    sub_0804495C();
}
