#include "global.h"

void *sub_08071E84(void *arg0, u32 arg1)
{
    struct Unk71E84 *entry;
    s32 count;

    entry = *(struct Unk71E84 **)gUnk_030040E4;
    count = *(u8 *)gUnk_030040C4 - 1;

    if (count != -1)
    {
        do
        {
            if (entry->unk16 == 0)
            {
                sub_08071E44(entry, arg0, (s16 *)arg1);
                entry->unk18 = *(u32 *)gUnk_030000C8;
                (*(u32 *)gUnk_030000C8)++;
                return (void *)entry->unk18;
            }
            entry = (struct Unk71E84 *)((u8 *)entry + 0x28);
            count--;
        } while (count != -1);
    }

    sub_08067B98((void *)0x083D2578);
    return (void *)-1;
}
