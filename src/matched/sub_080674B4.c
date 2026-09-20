#include "global.h"

// @ 0x080674b4
__attribute__((naked))
void sub_080674B4(void)
{
    asm(".syntax unified\nmovs r2, #0x00\nswi #5\nbx lr");
}
