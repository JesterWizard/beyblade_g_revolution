#include "global.h"

struct Unk38D10
{
    u8 filler_000[0x2FC];
    s32 unk2FC;
};

// @ 0x08038d10
void sub_08038D10(struct Unk38D10 *a)
{
    void **table;
    s32 i = 0;

    table = (void **)gUnk_030003E0;

    for (; i <= 3; i++)
    {
        void *entry = table[a->unk2FC + i];

        if (entry != 0)
            sub_08070AD4(&gBattleWork->unk023C[i], entry, 1);
        else
            sub_08070678(&gBattleWork->unk023C[i]);
    }
}

