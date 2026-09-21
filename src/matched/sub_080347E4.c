#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080347e4
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x080347e4
void sub_080347E4(struct Unk346C0 *a)
{
    struct Unk346C0Inner *p = a->unk00;

    if (p == 0)
        return;
    p->unk30 = a->unk2DC;
    p->unk4C = a->unk2D8;
    p->unk48 = a->unk2D4;
    p->unk34 = a->unk2E0;
}

