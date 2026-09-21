/* match-compiler: old_agbcc */
#include "global.h"

struct Unk71E84 *sub_08071F44(s32 arg0)
{
    struct Unk71E84 *entry;
    s32 count;

    entry = *(struct Unk71E84 **)gUnk_030040E4;
    count = *(u8 *)gUnk_030040C4 - 1;

    if (count != -1)
    {
        do
        {
            if (entry->unk16 != 0 && entry->unk18 == arg0)
                return entry;
            entry = (struct Unk71E84 *)((u8 *)entry + 0x28);
            count--;
        } while (count != -1);
    }

    return 0;
}
