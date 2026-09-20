#include "global.h"

// @ 0x08043b58
/* match-flags: -fprologue-bugfix */

struct Unk447CC *sub_08043B58(void)
{
    struct Unk447CC **table;
    struct Unk447CC *entry;
    u32 key;

    key = gMainWorkPtr->unk1690->unk00;
    table = (struct Unk447CC **)0x08096794;
    entry = *table;
    if (entry != 0)
    {
        table++;
        do
        {
            if ((u32)entry->unk00 == key)
                return entry;
            entry = *table++;
        } while (entry != 0);
    }
    return 0;
}
