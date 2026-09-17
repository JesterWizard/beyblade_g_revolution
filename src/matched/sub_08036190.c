#include "global.h"

// @ 0x08036190
void sub_08036190(u32 *a, u32 v1, u32 v2, u32 v3)
{
    a[0] = v1;
    a[1] = v2;
    a[2] = v3;
    a[3] = 0x7800;
    a[4] = 0x5000;
    a[5] = 0;
}
