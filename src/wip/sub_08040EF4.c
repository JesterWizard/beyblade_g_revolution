#include "global.h"

// @ 0x08040EF4
s32 sub_08040EF4(void *key)
{
    register u32 keyReg;
    register u32 offset;
    register const u32 *base;
    register const u32 *current;
    register const u8 *valueBase;
    u32 *list;
    u8 index;

    keyReg = (u32)key;
    base = (const u32 *)0x0808B2E4;
    if (*base != (u32)-1)
    {
        offset = 0;
        current = base;
        valueBase = (const u8 *)base + 4;
        for (;;)
        {
            if (*current == keyReg)
            {
                list = *(u32 **)(valueBase + offset);
                index = gMainWorkPtr->unk1818;
                return (s32)list[index];
            }
            base++;
            offset += 8;
            current++;
            if (*base == (u32)-1)
                break;
        }
    }
    return 0;
}
