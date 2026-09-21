#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08071b4c
void sub_08071B4C(void)
{
    u32 w = (u32)gData_04000084;
    u32 z = 0;
    u32 keep;
    u32 n;
    u32 scaled;
    u32 *sym;
    void *ptr;

    *(vu16 *)w = z;
    w -= 2;
    *(vu16 *)w = z;
    w += 0x42;
    z = w;
    keep = 0;
    *(vu32 *)w = keep;
    w += 0x0C;
    *(vu32 *)w = keep;
    w += 0x34;
    *(vu32 *)w = keep;
    w -= 4;
    *(vu32 *)w = keep;
    sym = gData_080BB8BC;
    ptr = (void *)gData_030040DC[0];
    n = gData_0300410C[0];
    scaled = n << 1;
    scaled += 0x20;
    n += scaled;
    _08073C4C(0, ptr, n, (void *)*sym);
    gData_030000C0[0] = keep;
    (void)z;
}
