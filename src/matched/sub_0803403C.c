#include "global.h"

// @ 0x0803403c
void sub_0803403C(struct Unk33F30 *a)
{
    u16 *disp;

    a->unk25 = 0;
    a->unk64 = 0;
    a->unk60 = 0;
    disp = (u16 *)(0x80 << 19);
    *disp &= 0x9FFF;
    sub_08033F24(a);
    sub_08034360(a);
    sub_08034414(a);
}

