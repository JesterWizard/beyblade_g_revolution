#include "global.h"

// @ 0x0803413c
void sub_0803413C(struct Unk33F30 *a)
{
    sub_08033F30(a, -0x80);
    a->unk25 = 0;
    sub_08034A68((struct Unk346C0 *)a->unk28, (u32)a->unk2C);
    sub_08034A68((struct Unk346C0 *)a->unk2C, (u32)a->unk28);
    a->unk64 = 0;
    sub_08035020((struct Unk346C0 *)a->unk2C, 0xB4);
    sub_08034414(a);
    sub_08034360(a);
}
