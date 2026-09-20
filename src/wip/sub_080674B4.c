#include "global.h"

// @ 0x080674b4
void sub_080674B4(void)
{
    register int r2 = 0;
    asm("swi 5" : : "r"(r2));
}
