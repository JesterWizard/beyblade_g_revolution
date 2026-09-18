#include "global.h"

// @ 0x08066ad4
void sub_08066AD4(struct Unk66AD4 *a)
{
    a->unk28C->unk08 = (a->unk304 << 12) + 0x2000;
    a->unk28C->unk0C = (a->unk308 * 0x1400) + 0x2C00;
}
