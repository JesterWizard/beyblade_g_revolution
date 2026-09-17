#include "global.h"

// @ 0x080705cc
void sub_080705CC(void *a)
{
    *(u8 *)((u8 *)a + 0x19) = 0x01;
}
