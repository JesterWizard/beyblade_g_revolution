#include "global.h"

// @ 0x0803403c
void sub_0803403C(struct Unk33F30 *a)
{
    a->unk25 = 0;
    a->unk64 = 0;
    a->unk60 = 0;
    *(u16 *)0x04000000 &= 0x9FFF;
    sub_08033F24(a);
    sub_08034360(a);
    sub_08034414(a);
}
