#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806fdb4
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x0806fdb4
struct Unk6FDB4 *sub_0806FDB4(struct Unk6FDB4 *p, u16 key)
{
    struct Unk6FDB4 *prev = 0;

    if (p != 0)
    {
        do
        {
            if (p->unk22 >= key)
                break;
            prev = p;
            p = p->unk04;
        } while (p != 0);
    }
    return prev;
}

