#include "global.h"
#include "ram_map.h"

s32 sub_08040EF4(void *key)
{
    u32 searchKey;
    u32 *cursor;
    u32 *keyp;
    u32 *valp;
    u32 off;
    u32 *vals;
    struct MainWork *mw;
    u8 index;

    searchKey = (u32)key;
    cursor = (u32 *)0x0808B2E4;
    if (*cursor == (u32)-1)
        return 0;

    off = 0;
    keyp = cursor;
    valp = cursor + 1;
    for (;;)
    {
        if (*keyp == searchKey)
        {
            vals = *(u32 **)((u8 *)valp + off);
            mw = *(struct MainWork **)0x03000198;
            index = *(u8 *)((u32)mw + 0x1818);
            return (s32)*(u32 *)((u8 *)vals + (index << 2));
        }
        cursor += 2;
        off += 8;
        keyp += 2;
        if (*cursor == (u32)-1)
            break;
    }
    return 0;
}
