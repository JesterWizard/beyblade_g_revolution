#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080691e4
// Sprite dimensions for OAM shape/size bits (b >> 14): with flags bit 0 a
// square of 2^(size+4) pixels, else the fixed wide/tall table. Stores the
// log2 width/height in unk5F/unk60 and returns the tile byte count.
u32 OamShapeToSize(struct Unk691E4 *a, u16 b, u16 flags)
{
    s32 size;
    s32 shape;
    u32 result;

    size = b >> 14;
    shape = size;
    if (flags & 1)
    {
        result = 1 << (size * 2 + 8);
        size += 4;
        a->unk5F = size;
        a->unk60 = size;
    }
    else
    {
        switch (shape)
        {
        case 0:
            result = 0x800;
            a->unk5F = 5;
            a->unk60 = 5;
            break;
        case 1:
            result = 0x1000;
            a->unk5F = 6;
            a->unk60 = 5;
            break;
        case 2:
            result = 0x1000;
            a->unk5F = 5;
            a->unk60 = 6;
            break;
        case 3:
            result = 0x2000;
            a->unk5F = 6;
            a->unk60 = 6;
            break;
        }
    }
    return result;
}

