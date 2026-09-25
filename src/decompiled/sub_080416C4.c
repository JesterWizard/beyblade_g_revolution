#include "global.h"
#include "gba/io_reg.h"

// @ 0x080416c4
void sub_080416C4(struct Unk40F4C *a)
{
    struct Unk026C *desc;
    u16 dispFlags;
    s32 i;
    u8 *walk;
    void *slot;

    desc = a->unk248;
    dispFlags = 0;
    sub_08041394((struct Unk41394 *)a);
    sub_08069894();
    walk = (u8 *)a;
    for (i = 0; i <= 3; i++)
    {
        if (i == 0)
            slot = desc->unk30;
        else if (i == 1)
            slot = desc->unk34;
        else if (i == 2)
            slot = desc->unk38;
        else
            slot = desc->unk3C;
        if (slot != 0)
        {
            a->unk220[i] = sub_08065E0C(walk, (u8)i, slot, 0, 0);
            dispFlags |= *(u16 *)(0x080908B4 + i * 2);
        }
        walk += 0x88;
    }
    if (desc->unk40 != 0)
        sub_080679A4(desc->unk40);
    if (desc->unk44 != 0)
        sub_080679C0(desc->unk44);
    VBlankIntrWait();
    REG_DISPCNT = dispFlags | 0x4100;
    sub_08069B78(0, 1, 2, 3);
}
