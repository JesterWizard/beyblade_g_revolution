#include "global.h"

void sub_0804109C(void *a_arg, void *b_arg)
{
    register struct Unk40F4C *a asm("r2");
    register struct Unk4109CInput *b asm("r3");

    a = a_arg;
    b = b_arg;
    a->unk248 = b;
    a->unk2D4 = 0;
    a->unk24C = (void *)b->unk00;
    a->unk250 = (void *)b->unk04;
    a->unk254 = (void *)b->unk08;
    a->unk258 = (void *)b->unk0C;
    a->unk240 = (void *)b->unk10;
    a->unk244 = (void *)b->unk14;
    a->unk25C = (void *)b->unk18;
    a->unk260 = (void *)b->unk1C;
    a->unk264 = (void *)b->unk20;
    a->unk268 = (void *)b->unk24;
    a->unk26C = (void *)b->unk28;
    a->unk270 = (void *)b->unk2C;
    a->unk2D9 = b->unk4E;

    if (b->unk48 != 0)
    {
        if ((a->unk324 & 0x20) != 0)
        {
            a->unk2D7 = 0;
            a->unk322 = 0;
            a->unk320 = 0;
            a->unk31E = 0;
            a->unk31C = 0;
        }
        else
        {
            a->unk2D7 = 1;
            a->unk322 = 1;
            a->unk320 = b->unk4C;
            a->unk31E = b->unk4A;
            a->unk31C = b->unk48;
        }
    }
    else
    {
        a->unk2D7 = 0;
        a->unk322 = 0;
        a->unk320 = 0;
        a->unk31E = 0;
        a->unk31C = 0;
    }
    a->unk324 &= ~0x21;
}
