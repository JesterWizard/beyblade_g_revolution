#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08046e7c
/* match-compiler: old_agbcc */
// Per-frame field update: refresh the two main objects' sort keys, tick objects,
// timers and effects, read d-pad movement (when active and allowed) into a
// direction for _08041E88, run collision (sub_0806C7D4) and proximity
// triggers, and handle the countdown and menu buttons.
void sub_08046E7C(u32 active)
{
    u32 dir;
    s32 speed;
    u32 mesh;

    VBlankIntrWait();
    gData_03000198->unk0428 = ~(gData_03000198->unk0374 >> 8);
    if (gData_03000198->unk0424 != NULL)
        sub_08070468((struct Unk6FDB4 *)gData_03000198->unk0424, gData_03000198->unk0428);
    if (gData_03000198->unk0500 != NULL)
    {
        gData_03000198->unk0504 = ~((s32)gData_03000198->unk0450 >> 8);
        sub_08070468((struct Unk6FDB4 *)gData_03000198->unk0500, gData_03000198->unk0504);
    }
    sub_0806EE48((struct Unk6EE48 *)gData_03000198);
    sub_08068418(&gData_03000198->unk036C);
    sub_0804188C();
    sub_08067CE8(&gData_03000198->unk036C, 0);
    if (gData_03000198->unk182C != 0)
    {
        sub_08068418(&gData_03000198->unk0448);
        sub_08067CE8(&gData_03000198->unk0448, 0);
    }
    ((void (*)(void))gData_080BB888[0])();
    sub_0806A6F8();
    sub_080474AC();
    TimerAdvance();
    sub_080462D4();
    dir = 0;
    gData_03000198->unk03AC = 0;
    gData_03000198->unk03B0 = 0;
    gData_03000198->unk180C = 0;
    if ((gData_03003F60 & 2) && gData_03000198->unk17CC > 0x10)
        speed = 0x200;
    else
        speed = 0x100;
    if (active != 0)
    {
        if (gData_03000198->unk180C == 0 && *(u32 *)gData_03000634 == 0 && gData_03000198->unk182B != 0)
        {
            if (gData_03003F60 & 0x20)
            {
                dir = 1;
                *(u32 *)gData_0300063C = dir;
                *(u32 *)gData_03000634 = sub_08047624(0);
                sub_08042784(1);
            }
            else if (gData_03003F60 & 0x10)
            {
                dir = 2;
                *(u32 *)gData_0300063C = dir;
                *(u32 *)gData_03000634 = sub_08047624(1);
                sub_08042784(2);
            }
            else if (gData_03003F60 & 0x40)
            {
                dir = 4;
                *(u32 *)gData_0300063C = dir;
                *(u32 *)gData_03000634 = sub_08047624(2);
                sub_08042784(4);
            }
            else if (gData_03003F60 & 0x80)
            {
                dir = 8;
                *(u32 *)gData_0300063C = dir;
                *(u32 *)gData_03000634 = sub_08047624(3);
                sub_08042784(8);
            }
            else if (gData_03004060 & 1)
            {
                dir = 0x10;
            }
            else if (gData_03004060 & 0x100)
            {
                sub_08060428();
                sub_08066390(9);
                sub_0804109C((struct Unk40F4C *)&gData_03000198->unk0530, sub_0806639C());
                gData_03000198->unk181C = 4;
                gData_03000198->unk1808 |= 0x100;
            }
        }
        else if (*(u32 *)gData_03000634 != 0)
        {
            (*(u32 *)gData_03000634)--;
            dir = *(u32 *)gData_0300063C;
            sub_08042784(dir);
        }
    }
    _08041E88((void *)dir, speed);
    gData_03000198->unk1838 = 0xFFFF;
    mesh = sub_08062A14();
    sub_0806C7D4(&gData_03000198->unk036C, mesh, 0, 0);
    sub_08062758(&gData_03000198->unk0524, (struct Unk68574 *)&gData_03000198->unk036C);
    sub_0804245C();
    sub_08059B74();
    HudRefreshStats();
    gData_03000198->unk1788++;
    if ((*(u32 *)&gData_03000198->unk1854 & 0xFF00FF00) == 0x100 && BtlCountLiveSlots() == 0x53)
    {
        if (--gData_03000198->unk1858 <= 0)
        {
            gData_03000198->unk1857 = 1;
            sub_08059DC8(0, gData_080979EC);
        }
    }
    if ((gData_03004060 & 8) && gData_03000198->unk180C == 0 && gData_03000198->unk185A == 1)
    {
        gData_03000198->unk184D = 1;
        sub_08066390(7);
        sub_0804109C((struct Unk40F4C *)&gData_03000198->unk0530, sub_0806639C());
        gData_03000198->unk181C = 3;
        sub_08060428();
    }
}

