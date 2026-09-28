/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

s32 PaletteSlotAcquire(void *palette)
{
    u16 key;
    s16 i;
    struct Unk3CC **slots;

    key = 0;
    slots = &gData_030003CC;
    while (gData_08079068[(s16)key] != 0 && gData_08079068[(s16)key] != (u32)palette)
        key++;
    if (*slots == NULL)
        return -1;
    for (i = 0; i < 16; i++)
    {
        if ((s16)key == (s16)(*slots)->unk00[i])
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
            ((void (*)(u32, void *, u32))gData_080BB8C0[0])(gData_08079358[(s16)key], (void *)(0x05000200 + i * 32), 0x20);
            return (s8)i;
        }
    }
    return -1;
}
