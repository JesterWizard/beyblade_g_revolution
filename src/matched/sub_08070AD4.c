#include "global.h"

// @ 0x08070ad4
u8 TextGroupSetString(struct TextGroup *a, void *b, u8 c)
{
    TextGroupClear(a);
    return TextGroupAppendString(a, b, c);
}

