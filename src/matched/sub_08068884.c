#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068884
/* match-compiler: old_agbcc */
void *AnimHalfwordBase(struct Unk68014 *a)
{
    u8 *p = (u8 *)a + (a->unk08 * 8 + 0x20);
    u8 *q = (u8 *)a + a->unk18;

    if (p == q)
        return 0;
    return p;
}

