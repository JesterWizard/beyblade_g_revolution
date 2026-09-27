#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080620d4
/* match-compiler: old_agbcc */
// Offsets every entry of the pointer array a->unk0C by (dx, dy) in 8.8 fixed
// point and snapshots the first entry's position into a->unk10/unk14.
// Declared non-void (retail epilogue is pop {r1}) but never returns a value.
s32 Unk62044OffsetPoints(struct Unk62044 *a, s32 dx, s32 dy)
{
    struct Unk620D4Entry **p;
    struct Unk620D4Entry *e;
    s32 i;

    if (a == NULL)
        return;
    if (a->unk0C == NULL)
        return;
    for (i = 0, p = a->unk0C; i <= 0x7F; i++)
    {
        e = p[i];
        if (e == NULL)
            return;
        e->unk08 += dx << 8;
        e->unk0C += dy << 8;
        if (i == 0)
        {
            a->unk10 = p[0]->unk08;
            a->unk14 = p[0]->unk0C;
        }
    }
}
