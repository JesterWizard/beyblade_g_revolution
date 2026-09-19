#include "global.h"

struct Unk31368Entry
{
    u8 filler_00[8];
    u32 unk08;
    u32 unk0C;
};

// @ 0x08031368
void sub_08031368(struct Unk31368Entry **arr, s32 n, u32 *out08, u32 *out0C)
{
    s32 i = n - 1;

    if (i > 0)
    {
        do
        {
            struct Unk31368Entry *entry = arr[i];

            if (entry != 0)
            {
                *out08 = entry->unk08;
                *out0C = entry->unk0C;
                return;
            }
            i--;
        } while (i > 0);
    }

    *out08 = 0;
    *out0C = 0;
}

