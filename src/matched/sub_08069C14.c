#include "global.h"

// @ 0x08069c14

u32 sub_08069C14(struct Unk69C14 *a)
{
    u32 v;

    v = *(u32 *)sub_08069988(a->unk5E);
    return (v << 30) >> 30;
}

