#include "global.h"

// @ 0x0803dbd0
__attribute__((naked))
void sub_0803DBD0(void)
{
    asm(".syntax unified\nadds r3, r0, #0x0\ncmp r3, #0x00\nblt _0803DC00\nldr r2, _0803DBF4 @ =0x080796DC\nldr r0, _0803DBF8 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _0803DBFC @ =0x00001818\nadds r0, r0, r1\nldrb r0, [r0, #0x00]\nlsls r1, r0, #0x02\nlsls r0, r3, #0x02\nadds r0, r0, r3\nlsls r0, r0, #0x03\nadds r1, r1, r0\nadds r1, r1, r2\nldr r0, [r1, #0x00]\nb _0803DC12\n.byte 0x00, 0x00\n_0803DBF4: .4byte 0x080796DC\n_0803DBF8: .4byte 0x03000198\n_0803DBFC: .4byte 0x00001818\n_0803DC00:\nldr r1, _0803DC14 @ =0x08097458\nldr r0, _0803DC18 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r2, _0803DC1C @ =0x00001818\nadds r0, r0, r2\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r0, [r0, #0x00]\n_0803DC12:\nbx lr\n_0803DC14: .4byte 0x08097458\n_0803DC18: .4byte 0x03000198\n_0803DC1C: .4byte 0x00001818");
}
