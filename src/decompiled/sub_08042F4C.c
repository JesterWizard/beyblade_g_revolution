#include "global.h"

// @ 0x08042F4C
void sub_08042F4C(s32 a, s32 b, s16 c, s32 d)
{
    struct Unk42E78 *row;
    s16 old;

    row = ((struct Unk42E78 *(*)(s32))sub_08042E78)(c);
    if (row != 0)
    {
        old = row->unk00;
        row->unk00 = a + 0x64 * d;
        if (b + d > 0)
            b += d;
        row->unk03 = b;
        DebugPrint((void *)0x083A2CF4, (void *)0x083A2D28, c, old, row->unk00, d);
    }
}
