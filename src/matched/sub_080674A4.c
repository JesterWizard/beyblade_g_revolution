#include "global.h"

// @ 0x080674a4
__attribute__((naked))
s32 sub_080674A4(s32 a, s32 b)
{
    asm(".syntax unified\nswi #6\nadds r0, r1, #0x0\nbx lr");
}
