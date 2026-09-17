#include "global.h"

// @ 0x080346a8
void sub_080346A8(void *a, u32 v)
{
    *(u32 *)((u8 *)a + 0x2f0) = v;
}
