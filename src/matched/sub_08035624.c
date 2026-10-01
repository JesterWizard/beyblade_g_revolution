#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035624
/* match-compiler: old_agbcc */
// Set the sort key of one of the three state slots (type 0/1/2 -> key at
// +0xD8/+0x1B4/+0x290, list node at +0xD4/+0x1B0/+0x28C) to the base key at
// a->unk00->unk00->unk22 plus `delta`, and re-sort the node if it exists.
//
// The key is stored a second time inside the `if`. It is load-bearing: the
// second store keeps the key address live past the node load, so global alloc
// gives it r4 (and the node address r2) as retail does. reload_cse then drops
// the store as a no-op, so it leaves no code behind.
void sub_08035624(struct Unk346C0 *a, u8 type, s8 delta)
{
    s32 value = a->unk00->unk00->unk22 + delta;

    switch (type)
    {
    case 0:
        a->unkD8 = value;
        if (a->unkD4 != NULL)
        {
            a->unkD8 = value;
            BtlObjListResort((struct Unk6FDB4 *)a->unkD4, value);
        }
        break;
    case 1:
        a->unk1B4 = value;
        if (a->unk1B0 != NULL)
        {
            a->unk1B4 = value;
            BtlObjListResort((struct Unk6FDB4 *)a->unk1B0, value);
        }
        break;
    case 2:
        a->unk290 = value;
        if (a->unk28C != NULL)
        {
            a->unk290 = value;
            BtlObjListResort((struct Unk6FDB4 *)a->unk28C, value);
        }
        break;
    }
}

