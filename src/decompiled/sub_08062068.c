#include "global.h"

s32 sub_08062068(struct Unk62068 *a, s32 b, s32 mode)
{
    s32 result;

    switch (mode)
    {
    case 0:
        result = a->unk1E - (b >> 1);
        break;
    case 2:
        result = a->unk1E;
        break;
    case 1:
        result = a->unk1E - b;
        break;
    }

    return result;
}
