#include "global.h"

void sub_0803531C(struct Unk35258 *a)
{
    u8 *flagsPtr;
    u8 mask;
    register u8 flags asm("r1");

    if (a->unk1C.unk70 == 0)
        sub_08035258(a, 0);
    if (a->unk1D4.unk70 == 0)
        sub_08035258(a, 2);
    if (a->unkF8.unk70 == 0)
        sub_08035258(a, 1);
    flagsPtr = &a->unk2C5;
    flags = *flagsPtr;
    mask = 1;
    if ((mask & flags) != 0)
        sub_08068418(&a->unk1C);
    flags = *flagsPtr;
    mask = 4;
    if ((mask & flags) != 0)
        sub_08068418(&a->unk1D4);
    flags = *flagsPtr;
    mask = 2;
    if ((mask & flags) != 0)
        sub_08068418(&a->unkF8);
}
