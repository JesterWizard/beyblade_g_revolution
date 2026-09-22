#include "global.h"

void sub_080348E8(struct Unk346C0 *a, u32 b)
{
    s32 *counter;
    u8 flag;
    u8 *flag_ptr;

    a->unk30E = sub_08035C64(a->unk00, 0x10000, 0x10000, 0xC8, 0x8000);
    if (sub_08035D1C(a->unk00, 0x10000, 0x10000) == 1)
        sub_08060254(4, 0x38, 7);
    sub_08035984(a->unk00);
    if (a->unk18 == 1)
        sub_08035884(&a->unk08);
    sub_08034894(a);
    if (a->unk310 != 0 &&
        a->unk2CC != 2 &&
        a->unk2CC != 6 &&
        a->unk2CC != 3 &&
        sub_08034FBC((struct Unk34FF8 *)a) != 0)
    {
        sub_08034A68(a, b);
    }
    sub_08034618(a);
    if (a->unk2CC == 7)
    {
        counter = &a->unk2FC;
        if (*counter >= 0)
        {
            sub_08034810(a, 0);
            (*counter)--;
        }
        else
        {
            a->unk2CC = 5;
            a->unk310 = 0;
            sub_0803484C((struct Unk3484C *)a);
            a->unk2F8 = -1;
        }
    }
    flag = a->unk310;
    if (flag == 0 && a->unk2CC == 5)
    {
        counter = &a->unk2F8;
        if (*counter >= 0)
        {
            flag_ptr = &a->unk312;
            if (*flag_ptr == 0)
            {
                sub_08035204(a, 0, 0x0A, -1);
                *flag_ptr = 1;
                a->unk2B0 = flag;
                a->unk2B4 = 8;
            }
            (*counter)--;
        }
        else if (a->unk312 == 1)
        {
            sub_08035204(a, 0, 0x0B, -1);
            a->unk08C = sub_08067FC8(&a->unk1C, 0);
            a->unk2B0 = flag;
            a->unk2B4 = 8;
            a->unk312 = flag;
        }
    }
}
