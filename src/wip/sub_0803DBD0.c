#include "global.h"

// @ 0x0803dbd0
#include "global.h"

/* match-flags: -fprologue-bugfix */

u32 sub_0803DBD0(u32 a)
{
    s32 index;
    u32 table;
    u32 sel;
    u32 off;
    u32 result;

    index = a;
    if (index >= 0)
    {
        table = 0x080796DC;
        sel = gMainWorkPtr->unk1818;
        off = sel << 2;
        result = index << 2;
        result = result + index;
        result <<= 3;
        off = off + result;
        off = off + table;
        result = *(u32 *)off;
        goto done;
    }
    table = 0x08097458;
    sel = gMainWorkPtr->unk1818;
    sel <<= 2;
    result = sel + table;
    result = *(u32 *)result;
done:
    return result;
}
