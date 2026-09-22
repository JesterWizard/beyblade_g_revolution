#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08065e0c
// Blit a keyed tile record: recover the record for `c`'s key (word >> 8), route
// its two cursors through sub_080674AC/B4, then hand [a, b, record->unk00, d, e] to
// sub_08068988. `b`/`d`/`e` truncate (u8/u16/u16) and the record's first word --
// not the record pointer -- is what the two helpers receive and what is returned
// paths use. Returning the pointer keeps the high-register live ranges retail has.
void *sub_08065E0C(void *a, u8 b, void *c, u16 d, u16 e)
{
    struct Unk68988 *p = BtlObjAlloc(*(u32 *)c >> 8);

    sub_080674AC(c, (void *)p->unk00);
    sub_080674B4();
    sub_08068988(a, b, p->unk00, d, e);
    return p;
}

