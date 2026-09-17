#include "global.h"

// @ 0x08035878
void sub_08035878(void *a, u32 v1, u32 v2, u32 v3)
{
    *(u32 *)((u8 *)a + 0x08) = v2;
    *(u32 *)((u8 *)a + 0x0c) = v3;
    *(u32 *)((u8 *)a + 0x04) = v1;
    *(u32 *)a = 0;
}
