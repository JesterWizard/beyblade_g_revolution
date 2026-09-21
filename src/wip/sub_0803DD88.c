#include "global.h"

// @ 0x0803dd88
// 30/40 same-size. Row lookup into the 40-byte-stride table at gData_0807A1F4,
// indexed by the u8 at gMainWorkPtr+0x1818. Retail: ldr r3,=table FIRST, then the
// gMainWorkPtr->unk1818 chain, ldrb r1,[r1] (idx lands in r1, clobbering the
// gMainWorkPtr temp), lsls r2,r1,#2 (idx*4), a*40 as (a*5)<<3 in r1, adds r2,r2,r1,
// adds r2,r2,r3, ldr r0,[r2]. `u8 *base = gData_0807A1F4;` before the expression is
// what moves the table load to the front; the residual is idx choosing r2 instead
// of r1 and the (idx*4 + a*40) sum being formed in the other operand order.
// Older form (no base local) is 7/40.
s32 sub_0803DD88(s32 a)
{
    u8 *base = gData_0807A1F4;

    return *(s32 *)(base + (gMainWorkPtr->unk1818 * 4 + a * 40));
}
