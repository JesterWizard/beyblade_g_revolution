#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08065560
/* match-compiler: old_agbcc */
// Copy three {unk08, unk0C} presets into the objects picked by the per-mode
// index triple. BUG: modes other than 0-2 leave `indices` unset.
void sub_08065560(struct Unk65560 *a)
{
    const u8 *indices;
    struct Unk65560Source *source;
    s32 i;
    struct Unk705DC **table;
    const u8 *p;
    struct Unk705DC **slot;
    struct Unk705DC **slot2;

    switch (a->unk2D5)
    {
    case 0:
        indices = gData_080BAF61;
        break;
    case 1:
        indices = gData_080BAF64;
        break;
    case 2:
        indices = gData_080BAF67;
        break;
    }
    table = a->unk274;
    p = indices;
    source = gData_080BAF00;
    for (i = 2; i >= 0; i--)
    {
        slot = &table[*p];
        (*slot)->unk08 = source->unk00;
        slot2 = &table[*p];
        (*slot2)->unk0C = source->unk04;
        p++;
        source++;
    }
}

