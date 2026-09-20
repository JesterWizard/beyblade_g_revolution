#include "global.h"

// @ 0x08042b00
__attribute__((naked))
void sub_08042B00(void)
{
    asm(".syntax unified\nldr r2, _08042B1C @ =0x08090FF0\nldr r1, _08042B20 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r3, _08042B24 @ =0x00001818\nadds r1, r1, r3\nldrb r1, [r1, #0x00]\nlsls r1, r1, #0x02\nadds r1, r1, r2\nldr r1, [r1, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nbx lr\n.byte 0x00, 0x00\n_08042B1C: .4byte 0x08090FF0\n_08042B20: .4byte 0x03000198\n_08042B24: .4byte 0x00001818");
}
