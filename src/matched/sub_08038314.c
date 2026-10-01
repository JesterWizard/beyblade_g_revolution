#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08038314
/* match-compiler: old_agbcc */

void sub_08038314(struct Unk38314 *a, s32 b)
{
    if (--a->unk304 > 0 && (gData_03004060 & 3) == 0)
        return;

    a->unk2FC = b;
    sub_08062044(&gData_03000290->unk19C[0]);
    sub_08062044(&gData_03000290->unk19C[1]);
    sub_08062044(&gData_03000290->unk19C[2]);
    sub_08062044(&gData_03000290->unk19C[3]);
}

