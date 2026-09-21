#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080617c4
/* match-compiler: old_agbcc */
// Register the object at gUnk_03000798 with the engine: store `a` and `b` in the two
// slots at +0x88/+0x8C, publish `a`'s two bytes at +0xA0/+0xA2, then derive the word at
// +0x9C from the halfword just written at +0xA0 (read back, not the local, which is why
// it survives as a reload). The `& 1` test on a->unk0C comes first and returns early.
// The table is a real typed lvalue (gUnk_03000798) so agbcc keeps the literal in one
// register instead of re-materialising it.
void sub_080617C4(struct Unk617C4 *a, u32 b)
{
    struct Unk0798 *s;

    if ((a->unk0C & 1) == 0)
        return;
    s = gUnk_03000798;
    s->unk88 = a;
    s->unk8C = b;
    s->unkA0 = a->unk04;
    s->unkA2 = a->unk05;
    s->unk9C = s->unkA0 >> 2;
}

