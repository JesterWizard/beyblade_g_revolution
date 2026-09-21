#include "global.h"

// @ 0x0803ddb0
// 27/40 same-size. tbl[a - 1] holds a pointer; index it by gMainWorkPtr->unk1818.
// Retail: ldr r1,=table; subs r0,#1; lsls; adds (so `(a - 1) * 4`, NOT `a * 4 - 4`
// which is what a2d-array form gives); then the 0x03000198/0x1818 chain; then
// ldr r2,[r0] (the entry) BEFORE ldrb r1,[r1] (the index); then ldr r0,[r2 + idx*4].
// Residual: agbcc schedules the index load first and puts the entry in r0.
// `tbl[a-1][idx]` form is also 27/40; splitting the entry into a local drops to
// 21/40 because the table pool load moves after the (a-1)*4 arithmetic.
void *sub_0803DDB0(s32 a)
{
    u32 *entry = (u32 *)(gData_0807AEEC + (a - 1) * 4);

    return (void *)*(u32 *)((u8 *)*entry + gMainWorkPtr->unk1818 * 4);
}
