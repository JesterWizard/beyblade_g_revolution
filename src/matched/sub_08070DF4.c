#include "global.h"

// @ 0x08070df4
u8 TextGroupSetNumber(struct TextGroup *a, void *b, u8 c)
{
    TextGroupClear(a);
    return TextGroupAppendNumber(a, (s32)b, c);
}

