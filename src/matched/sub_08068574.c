#include "global.h"

// @ 0x08068574
void sub_08068574(void *a, u16 v1, u16 v2, u16 v3)
{
    *(u16 *)((u8 *)a + 0x9a) = v1;
    *(u16 *)((u8 *)a + 0x9c) = v2;
    *(u16 *)((u8 *)a + 0x9e) = v3;
}
