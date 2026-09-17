#include "global.h"

// @ 0x080338e4
void sub_080338E4(void *a, u32 v)
{
    *(u16 *)a = 0;
    *(u32 *)((u8 *)a + 4) = v;
    *(u16 *)((u8 *)a + 2) = 0;
}
