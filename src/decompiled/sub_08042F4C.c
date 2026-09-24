#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042f4c
#include "global.h"
#include "data_symbols.h"

void sub_08042F4C(s32 a, s32 b, s32 c, s32 d)
{
    struct Unk42E78 *row;
    s32 old;
    s32 scaled;

    row = (struct Unk42E78 *)sub_08042E78((u32)c);
    if (row != 0)
    {
        old = row->unk00;
        scaled = 0x64 * d;
        row->unk00 = a + scaled;
        scaled = b + d;
        if (scaled > 0)
            b = scaled;
        row->unk03 = (u8)b;
        DebugPrint((void *)gData_083A2CF4, (void *)gData_083A2D28, c, old, row->unk00, d);
    }
}

