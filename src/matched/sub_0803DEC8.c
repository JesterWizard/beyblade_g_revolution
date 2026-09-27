#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803dec8
/* match-compiler: old_agbcc */
// Claim the first free unk08D0 record (unk087C[i] == 0). A negative `row`
// copies template `id` from gData_0807A1F4 and tags it with (id, slot);
// otherwise the record comes from blade row sub_08042E78(row).
void sub_0803DEC8(u16 id, u8 row, u8 slot)
{
    s32 i;
    struct Unk42E78 *blade;

    for (i = 0; i <= 0x52; i++)
    {
        if ((s8)gData_03000198->unk087C[i] == 0)
        {
            if ((s8)row < 0)
            {
                gData_03000198->unk08D0[i].unk1D = gData_0807A1F4[(s16)id].unk1D;
                gData_03000198->unk08D0[i].unk21 = gData_0807A1F4[(s16)id].unk21;
                gData_03000198->unk08D0[i].unk20 = gData_0807A1F4[(s16)id].unk20;
                gData_03000198->unk08D0[i].unk26 = gData_0807A1F4[(s16)id].unk26;
                gData_03000198->unk08D0[i].unk1F = gData_0807A1F4[(s16)id].unk1F;
                gData_03000198->unk08D0[i].unk1E = gData_0807A1F4[(s16)id].unk1E;
                gData_03000198->unk08D0[i].unk1C = id;
                gData_03000198->unk08D0[i].unk23 = slot;
                gData_03000198->unk08D0[i].unk14 = gData_0807A1F4[(s16)id].unk14;
                gData_03000198->unk08D0[i].unk18 = gData_0807A1F4[(s16)id].unk18;
            }
            else
            {
                blade = sub_08042E78((s8)row);
                gData_03000198->unk08D0[i].unk1D = blade->unk08.unk1D;
                gData_03000198->unk08D0[i].unk21 = blade->unk08.unk21;
                gData_03000198->unk08D0[i].unk20 = blade->unk08.unk20;
                gData_03000198->unk08D0[i].unk26 = blade->unk08.unk26;
                gData_03000198->unk08D0[i].unk23 = blade->unk08.unk23;
                gData_03000198->unk08D0[i].unk1F = blade->unk08.unk1F;
                gData_03000198->unk08D0[i].unk1C = blade->unk08.unk1C;
                gData_03000198->unk08D0[i].unk1E = blade->unk08.unk1E;
                gData_03000198->unk08D0[i].unk14 = blade->unk08.unk14;
                gData_03000198->unk08D0[i].unk18 = blade->unk08.unk18;
            }
            gData_03000198->unk087C[i] = 1;
            gData_03000198->unk0877++;
            gData_03000198->unk1861[gData_03000198->unk08D0[i].unk1C]++;
            return;
        }
    }
}

