/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x0803ddb0
u32 sub_0803DDB0(u32 a)
{
    u32 *t = (u32 *)gData_0807AEEC;
    u32 i = a - 1;
    u8 *p = (u8 *)gData_03000198[0];

    return ((u32 *)(t[i]))[*(u8 *)(p + 0x1818)];
}
