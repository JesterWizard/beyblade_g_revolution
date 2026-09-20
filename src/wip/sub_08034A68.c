#include "global.h"

// @ 0x08034a68
void sub_08034A68(struct Unk346C0 *a, u32 b)
{
    u32 off;
    u32 p;
    u8 zero;
    u8 status;

    p = (u32)a;
    off = 0xC4;
    off <<= 2;
    p += off;
    zero = 0;
    *(u8 *)p = zero;
    off = 0xC5;
    off <<= 2;
    p = (u32)a + off;
    status = *(u8 *)p;
    if (status == 1)
    {
        off -= 0x1C;
        *(u32 *)((u32)a + off) = 0x3C;
        *(u8 *)p = zero;
    }
    off = 0x311;
    p = (u32)a + off;
    *(u8 *)p = zero;
    off -= 2;
    p = (u32)a + off;
    *(u8 *)p = zero;
    off = 0xB3;
    off <<= 2;
    p = (u32)a + off;
    *(u32 *)p = 5;
    sub_08035238((struct Unk35258 *)a);
    sub_080347E4(a);
    off = 0xC3;
    off <<= 2;
    p = (u32)a + off;
    if (*(u8 *)p == 1)
    {
        sub_08034FDC((struct Unk34FF8 *)a, b);
        sub_08035884(&a->unk08);
    }
}
