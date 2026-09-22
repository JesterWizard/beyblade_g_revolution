#include "global.h"

void sub_08065560(struct Unk65560 *a)
{
    struct Unk65560 *data;
    const u8 *indices;
    struct Unk65560Source *source;
    struct Unk705DC **table;
    s32 i;

    data = a;
    table = data->unk274;
    switch (data->unk2D5)
    {
    case 0:
        indices = (const u8 *)0x080BAF61;
        break;
    case 1:
        indices = (const u8 *)0x080BAF64;
        break;
    case 2:
        indices = (const u8 *)0x080BAF67;
        break;
    default:
        return;
    }
    source = (struct Unk65560Source *)0x080BAF00;
    for (i = 2; i >= 0; i--)
    {
        a->unk274[*indices]->unk08 = source->unk00;
        a->unk274[*indices]->unk0C = source->unk04;
        indices++;
        source++;
    }
}
