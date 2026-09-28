/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void sub_08043DB4(s32 a, void *b, s32 c, s32 d, s32 e)
{
    u32 tmp;
    u32 r;
    void *obj;
    s32 i;
    s8 ok;
    s32 none;

    gData_03000198->unk17F0 = 0;
    gData_03000198->unk17F2 = 0;
    REG_BLDY = 0;
    gData_03000198->unk185A = 0;
    if (d != 0)
        sub_0804438C(-1);
    sub_080447CC();
    sub_08062728(&gData_03000198->unk0524);
    sub_08041980();
    sub_08059C6C();
    VramSlotsRelease();
    sub_0802D598();
    sub_0802DEA0();
    sub_08043ADC();
    sub_08045D3C(0x18, 4, &tmp);
    if (tmp != 0)
    {
        do
            r = RandRange(6);
        while (gData_03000198->unk1780 == r);
        _0805FED4((void *)r);
    }
    ok = sub_0806644C();
    none = -1;
    if (ok >= 0)
    {
        sub_08068808((struct Unk68574 *)&gData_03000198->unk036C);
        sub_0802DEA0();
        sub_080611F0();
        sub_080632F8();
        VramSlotsInit();
        sub_08069894();
    }
    if (gData_03000198->unk17A8 != -0x4000)
    {
        gData_03000198->unk0868 = gData_03000198->unk17A8;
        gData_03000198->unk086C = gData_03000198->unk17AC;
        gData_03000198->unk0370 = gData_03000198->unk0868;
        gData_03000198->unk0374 = gData_03000198->unk086C;
        gData_03000198->unk17A8 = -0x4000;
        gData_03000198->unk17AC = -0x4000;
    }
    sub_080442FC(b, (void *)a, c, e);
    gData_03000198->unk0358 |= 0x800;
    sub_0806121C((struct Unk617C4 *)0x082BCD00, 0x080B738E, 0x1C0, 0x1C, 0x10, 1, 4, 0x0F);
    sub_08069B78(gData_03000198->unk1690->unk74_0, gData_03000198->unk1690->unk74_2, gData_03000198->unk1690->unk74_4, 0);
    sub_08047594();
    sub_080444BC();
    sub_0806EE24((struct Unk6EE24 *)gData_03000198);
    sub_080473E4();
    if (gData_03000198->unk1843 == 1 && gData_03000198->unk18B4 != none)
    {
        obj = sub_08041DB4(gData_03000198->unk18B4, 0);
        if (obj != NULL)
        {
            sub_08068418(obj);
            sub_0806F174((struct Unk6F174 *)gData_03000198, obj);
            sub_08046E7C(0);
            for (i = 0; i < 64; i++)
                sub_0806EE48((struct Unk6EE48 *)gData_03000198);
        }
        else
        {
            sub_0806F174((struct Unk6F174 *)gData_03000198, b);
        }
    }
    else
    {
        sub_0806F174((struct Unk6F174 *)gData_03000198, b);
    }
    gData_03000198->unk1794 = -1;
    gData_03000198->unk17E4 = -1;
    gData_03000198->unk1790 = -1;
    gData_03000198->unk178C = -1;
    gData_03000198->unk17CC = 0;
    sub_08045D3C(0x18, 4, &tmp);
    if (tmp != 0)
    {
        sub_080428C4();
        switch (gData_03000198->unk1828)
        {
        case 0:
            BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk036C, 5);
            gData_03000198->unk039D &= 2;
            gData_03000198->unk1810 = 0x40;
            if (gData_03000198->unk182C != 0)
            {
                BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk0448, 5);
                gData_03000198->unk0479 &= 2;
                sub_080429CC();
            }
            break;
        case 1:
            BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk036C, 5);
            gData_03000198->unk039D |= 1;
            gData_03000198->unk1810 = 0x20;
            if (gData_03000198->unk182C != 0)
            {
                BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk0448, 5);
                gData_03000198->unk0479 |= 1;
                sub_080429CC();
            }
            break;
        case 2:
            BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk036C, 6);
            gData_03000198->unk039D = 0;
            gData_03000198->unk1810 = 0x80;
            if (gData_03000198->unk182C != 0)
            {
                BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk0448, 6);
                gData_03000198->unk0479 = 0;
                sub_080429CC();
            }
            break;
        case 3:
            BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk036C, 7);
            gData_03000198->unk039D = 0;
            gData_03000198->unk1810 = 0x100;
            if (gData_03000198->unk182C != 0)
            {
                BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk0448, 7);
                gData_03000198->unk0479 = 0;
                sub_080429CC();
            }
            break;
        }
    }
    if (gData_03000198->unk182C != 0)
        sub_08044A20();
    sub_08045D3C(0x18, 1, 0);
    gData_03000198->unk1808 &= ~0x2000;
    sub_0805DA70();
    switch (gData_03000198->unk185F)
    {
    case 10:
        BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk036C, 6);
        gData_03000198->unk039D = 0;
        gData_03000198->unk1810 = 0x80;
        break;
    case 11:
        BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk036C, 7);
        gData_03000198->unk039D = 0;
        gData_03000198->unk1810 = 0x100;
        break;
    case 8:
        BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk036C, 5);
        gData_03000198->unk039D &= 2;
        gData_03000198->unk1810 = 0x40;
        break;
    case 9:
        BtlEntitySelectByKeyDefault((struct Unk680CC *)&gData_03000198->unk036C, 5);
        gData_03000198->unk039D |= 1;
        gData_03000198->unk1810 = 0x20;
        break;
    }
    sub_0804438C(1);
    BtlClearUnk1834();
    gData_03000198->unk185A = 1;
    gData_03000198->unk185F = -1;
    ((void (*)(s32))sub_08066440)(-1);
}
