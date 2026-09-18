#include "global.h"

// @ 0x08036264
void sub_08036264(struct Unk36264 *out, struct Unk360BC *a, struct Unk360BC *b, s32 scale)
{
    s32 dx;
    s32 dy;
    s32 dist;

    dx = (a->unk0C - b->unk0C) >> 8;
    dy = (a->unk10 - b->unk10) >> 8;
    dist = sub_080674B0(dx * dx + dy * dy) << 16;
    out->unk00 = a->unk0C + ((scale * ((b->unk0C - a->unk0C) >> 1)) >> 8);
    out->unk04 = a->unk10 + ((scale * ((b->unk10 - a->unk10) >> 1)) >> 8);
    out->unk08 = (((u32)dist >> 18) + 0xFFFFFEFC) << 8;
}

