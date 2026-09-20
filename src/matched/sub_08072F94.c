#include "global.h"

// @ 0x08072f94
u32 sub_08072F94(void)
{
    u32 tmp[2];
    u32 *ptr;

    tmp[0] = gBtlLookupBase;
    ptr = (u32 *)gBtlLookupPtr;
    tmp[0] = tmp[0] + *ptr;
    return *(u8 *)tmp[0];
}

