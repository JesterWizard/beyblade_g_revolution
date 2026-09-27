#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806ff58
/* match-compiler: old_agbcc */
// Initialise sprite `dst` from template `src` at (x, y): pack the OAM
// attribute words (shape/size from src->unk07; 16-colour flag and palette
// from src->unk0C; object mode + mosaic; flip; priority) and point unk28 at
// the template graphics.
// The `mode` temporary keeps agbcc from re-associating the 0x1000 constant.
void sub_0806FF58(struct Unk705DC *dst, struct Unk6FF58Src *src, u32 x, u32 y, u8 objMode, u8 priority, u8 flip, u16 h)
{
    s8 shapeSize;
    u8 palette;
    u32 mode;

    shapeSize = src->unk07;
    palette = src->unk0C;
    dst->unk2C = src;
    dst->unk1C = flip;
    dst->unk08 = x;
    dst->unk0C = y;
    dst->unk10 = ((shapeSize & 3) << 14) | ((~palette & 1) << 13) | (mode = ((objMode & 3) << 10) | 0x1000)
               | ((shapeSize & 0xC) << 28) | ((flip & 3) << 28);
    dst->unk14 = (((palette >> 1) & 0xF) << 12) | ((priority & 3) << 10);
    dst->unk28 = (u8 *)src + (src->unk1C != 0 ? src->unk1C : src->unk10);
    dst->unk16 = src->unk06;
    dst->unk18 = h;
    dst->unk1A = 0xFFFF;
    dst->unk1C = 0;
    dst->unk20 = 0;
    dst->unk24 = -1;
    dst->unk1E = 0;
}

