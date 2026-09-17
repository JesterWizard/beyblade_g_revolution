#include "global.h"

// @ 0x08068584
void sub_08068584(void *a, u16 v1, u16 v2)
{
    *(u16 *)((u8 *)a + 0xa0) = v1;
    *(u16 *)((u8 *)a + 0xa2) = v2;
}
