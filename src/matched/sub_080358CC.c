#include "global.h"

// @ 0x080358cc
void sub_080358CC(void *a)
{
    *(u32 *)((u8 *)a + 0x08) = 0;
    *(u32 *)((u8 *)a + 0x0c) = 0;
    *(u32 *)((u8 *)a + 0x04) = 0;
}
