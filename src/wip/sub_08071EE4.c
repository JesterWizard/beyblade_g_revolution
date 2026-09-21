#include "global.h"
void *sub_08071EE4(void *a, u32 b)
{
    struct Unk71E84 *e = *(struct Unk71E84 **)gData_030040E4;
    s32 count = *(u8 *)gData_030040C4 - 1;

    while (count != -1)
    {
        if (e->unk16 == 0)
        {
            sub_08071E44(e, a, (s16 *)b);
            e->unk18 = *(u32 *)gData_030000C8;
            (*(u32 *)gData_030000C8)++;
            return (void *)e->unk18;
        }
        e = (struct Unk71E84 *)((u8 *)e + 0x28);
        count--;
    }
    sub_08067B98((void *)gData_083D2578);
    return (void *)-1;
}
