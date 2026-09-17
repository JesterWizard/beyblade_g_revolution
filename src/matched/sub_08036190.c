#include "global.h"

// @ 0x08036190
void sub_08036190(struct Unk36190 *a, u32 v1, u32 v2, u32 v3)
{
    a->unk00 = v1;
    a->unk04 = v2;
    a->unk08 = v3;
    a->unk0C = 0x7800;
    a->unk10 = 0x5000;
    a->unk14 = 0;
}
