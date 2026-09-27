#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068118
/* match-compiler: old_agbcc */
void sub_08068118(struct Unk68118 *a)
{
    struct Unk68118Table *table;
    u16 next;
    s32 arg;

    table = (struct Unk68118Table *)((u8 *)a->unk00 + a->unk00->unk18 + a->unk1C);
    if (a->unk1E < table->unk04 - 1)
    {
        next = a->unk1E + 1;
    }
    else
    {
        next = 0;
        if ((s16)a->unk2E != -1)
        {
            arg = a->unk1A;
            BtlEntitySelectByKey((struct Unk680CC *)a, a->unk2E, 0xFFFF);
            if (a->unkC0 != NULL)
                _08073C48(a, (void *)arg, a->unkC0);
            return;
        }
    }
    a->unk1E = next;
    sub_08068180((struct Unk68598 *)a, ((u16 *)table)[next + 4]);
}


