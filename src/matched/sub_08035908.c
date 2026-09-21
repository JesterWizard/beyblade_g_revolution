#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035908
/* match-compiler: old_agbcc */
// AABB-up-front test: walk the +4 sibling array. Returns 0 as soon as an entry
// whose +0 span contains v is found (v <= unk00 + unk04), else 1. The
// `if (e != 0) { while (...) } return 1` shape is required: an early
// `if (e == 0) return 1;` makes agbcc emit the opposite branch layout
// (`bne` + fall-through) and floors at 18/36.
u8 sub_08035908(struct Unk35878 *a)
{
    struct Unk35878 *e = (struct Unk35878 *)a->unk04;
    s32 v = a->unk00;

    if (e != 0)
    {
        while (e->unk08 != 0)
        {
            if (v <= (s32)(e->unk00 + e->unk04))
                return 0;
            e++;
        }
    }
    return 1;
}

