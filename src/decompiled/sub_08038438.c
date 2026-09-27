/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

s32 sub_08038438(void *palette)
{
    u16 key;
    s16 i;
    struct Unk3CC **slots = &gUnk_030003CC;

    key = 0;
    while (gData_08079068[(s16)key] != 0 && gData_08079068[(s16)key] != (u32)palette)
        key++;
    if (*slots == NULL)
        return -1;
    for (i = 0; i < 16; i++)
    {
        if ((s16)(*slots)->unk00[i] == (s16)key)
        {
            (*slots)->unk22[i]++;
            return (s8)i;
        }
    }
    for (i = 0; i < 16; i++)
    {
        if ((((*slots)->unk20 >> i) & 1) == 0)
        {
            (*slots)->unk00[i] = key;
            (*slots)->unk20 |= 1 << i;
            (*slots)->unk22[i] = 1;
            _08073C4C((void *)gData_08079358[(s16)key], (void *)(0x05000200 + i * 32), 0x20, (void *)gData_080BB8C0[0]);
            return (s8)i;
        }
    }
    return -1;
}
