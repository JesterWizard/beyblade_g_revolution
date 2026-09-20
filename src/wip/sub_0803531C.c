#include "global.h"

void sub_0803531C(struct Unk35258 *a)
{
    if (a->unk1C.unk70 == 0)
        sub_08035258(a, 0);
    if (a->unk1D4.unk70 == 0)
        sub_08035258(a, 2);
    if (a->unkF8.unk70 == 0)
        sub_08035258(a, 1);
    if ((a->unk2C5 & 1) != 0)
        sub_08068418(&a->unk1C);
    if ((a->unk2C5 & 4) != 0)
        sub_08068418(&a->unk1D4);
    if ((a->unk2C5 & 2) != 0)
        sub_08068418(&a->unkF8);
}
