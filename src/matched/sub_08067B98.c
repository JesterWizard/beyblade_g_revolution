#include "global.h"

// @ 0x08067b98
__attribute__((naked))
void sub_08067B98(void *a, ...)
{
    asm("push {r0, r1, r2, r3}\nadd sp, #0x10\n bx lr");
}

