#include "global.h"

// @ 0x080674b4
void sub_080674B4(void)
{
    asm volatile("movs r2, #0");
    asm("swi 5");
}
