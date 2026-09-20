#include "global.h"

// @ 0x0803ddd8
s32 sub_0803DDD8(s32 a)
{
    register u32 r1 = 0x0807AEFC;
    register u32 r0 = a;
    register u32 r2;
r0 = r0 - 1;
    r0 = (r0 << 2) + r1;
    r2 = *(u32 *)r0;
    r1 = 0x03000198;
    r1 = *(u32 *)r1;
    r2 = 0x1818;
    r1 = r1 + r2;
    r2 = *(u32 *)r0;
    r1 = *(u8 *)r1;
    r0 = r1 << 2;
    r0 = r0 + r2;
    return *(s32 *)r0;
}
