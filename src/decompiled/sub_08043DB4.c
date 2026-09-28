/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void FieldEnter(s32 a, void *b, s32 c, s32 d, s32 e)
{
    u32 tmp;
    u32 r;
    void *obj;
    s32 i;
    s8 ok;
    s32 none;

    gData_03000198->unk17F0 = 0;
    gData_03000198->unk17F2 = 0;
    REG_BLDALPHA = 0;
    gData_03000198->unk185A = 0;
    if (d != 0)
        ScreenBrightnessFade(-1);
    MapRunEntryScript();
    BufferClearWords(&gData_03000198->unk0524);
    sub_08041980();
    TasksDestroyAll();
    VramSlotsRelease();
    sub_0802D598();
    sub_0802DEA0();
    sub_08043ADC();
    EventFlagOp(0x18, 4, &tmp);
    if (tmp != 0)
    {
        do
            r = RandRange(6);
        while (gData_03000198->bgmTrack == r);
        _0805FED4((void *)r);
    }
    ok = sub_0806644C();
    none = -1;
    if (ok >= 0)
    {
        SceneObjFreeResources((struct Actor *)&gData_03000198->unk036C);
        sub_0802DEA0();
        TextWindowClose();
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
    TextWindowOpen((struct Unk617C4 *)0x082BCD00, 0x080B738E, 0x1C0, 0x1C, 0x10, 1, 4, 0x0F);
    BgSetPriorities(gData_03000198->unk1690->unk74_0, gData_03000198->unk1690->unk74_2, gData_03000198->unk1690->unk74_4, 0);
    SparklesHide();
    MapLoadObjects();
    sub_0806EE24((struct Unk6EE24 *)gData_03000198);
    sub_080473E4();
    if (gData_03000198->unk1843 == 1 && gData_03000198->unk18B4 != none)
    {
        obj = sub_08041DB4(gData_03000198->unk18B4, 0);
        if (obj != NULL)
        {
            SceneObjUpdate(obj);
            CameraSetTarget((struct Unk6F174 *)gData_03000198, obj);
            FieldUpdateFrame(0);
            for (i = 0; i < 64; i++)
                CameraUpdate((struct MapView *)gData_03000198);
        }
        else
        {
            CameraSetTarget((struct Unk6F174 *)gData_03000198, b);
        }
    }
    else
    {
        CameraSetTarget((struct Unk6F174 *)gData_03000198, b);
    }
    gData_03000198->unk1794 = -1;
    gData_03000198->unk17E4 = -1;
    gData_03000198->unk1790 = -1;
    gData_03000198->unk178C = -1;
    gData_03000198->unk17CC = 0;
    EventFlagOp(0x18, 4, &tmp);
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
    EventFlagOp(0x18, 1, 0);
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
    ScreenBrightnessFade(1);
    BtlClearUnk1834();
    gData_03000198->unk185A = 1;
    gData_03000198->unk185F = -1;
    ((void (*)(s32))sub_08066440)(-1);
}
