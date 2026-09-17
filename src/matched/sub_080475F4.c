#include "global.h"

// @ 0x080475f4
__attribute__((naked))
void sub_080475F4(void)
{
    asm(".syntax unified\nldr r0, _08047614 @ =0x03000630\nldr r2, [r0, #0x00]\ncmp r2, #0x00\nbeq _08047610\nldr r0, _08047618 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r3, _0804761C @ =0x00001798\nadds r1, r0, r3\nldr r1, [r1, #0x00]\nstr r1, [r2, #0x40]\nldr r1, _08047620 @ =0x0000179C\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nstr r0, [r2, #0x44]\n_08047610:\nbx lr\n.byte 0x00, 0x00\n_08047614: .4byte 0x03000630\n_08047618: .4byte 0x03000198\n_0804761C: .4byte 0x00001798\n_08047620: .4byte 0x0000179C");
}
