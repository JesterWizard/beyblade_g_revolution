#include "global.h"
#include "ram_map.h"
#include "battle.h"

void sub_08035624(struct Unk346C0 *a, u8 type, s32 delta)
{
    s32 value = a->unk00->unk00->unk22 + (s8)delta;

    switch (type)
    {
    case 0:
        a->unkD8 = value;
        if (a->unkD4 == NULL)
            break;
        sub_08070468((struct Unk6FDB4 *)a->unkD4, value);
        break;
    case 1:
        a->unk1B4 = value;
        if (a->unk1B0 == NULL)
            break;
        sub_08070468((struct Unk6FDB4 *)a->unk1B0, value);
        break;
    case 2:
        a->unk290 = value;
        if (a->unk28C == NULL)
            break;
        sub_08070468((struct Unk6FDB4 *)a->unk28C, value);
        break;
    }
}
