#include "global.h"

// @ 0x08033ea4
void sub_08033EA4(struct Unk33F30 *a)
{
    u32 dst;
    u32 n;

    dst = 0xA0;
    dst <<= 19;
    n = 0x80;
    n <<= 1;
    sub_080726A4((struct Unk726A4 *)a, dst, 0, n, 8);
    sub_08072A38(a, 0xC0, 0xC, 4, 3, 0xA, 0xA, 0xA, 0x1F);
}

