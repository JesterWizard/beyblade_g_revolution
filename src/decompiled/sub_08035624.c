/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

void sub_08035624(struct Unk346C0 *a, u8 type, s32 delta)
{
    s32 value = a->unk00->unk00->unk22 + (s8)delta;

    switch (type)
    {
    case 0:
        do { do { do {
        a->unkD8 = value;
        if (a->unkD4 != NULL)
            BtlObjListResort((struct Unk6FDB4 *)a->unkD4, (u16)value);
        } while (0); } while (0); } while (0);
        break;
    case 1:
        do { do { do {
        a->unk1B4 = value;
        if (a->unk1B0 != NULL)
            BtlObjListResort((struct Unk6FDB4 *)a->unk1B0, (u16)value);
        } while (0); } while (0); } while (0);
        break;
    case 2:
        do { do { do {
        a->unk290 = value;
        if (a->unk28C != NULL)
            BtlObjListResort((struct Unk6FDB4 *)a->unk28C, (u16)value);
        } while (0); } while (0); } while (0);
        break;
    }
}
