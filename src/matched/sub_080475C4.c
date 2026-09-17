#include "global.h"

// @ 0x080475c4
__attribute__((naked))
void sub_080475C4(void)
{
    asm(".syntax unified\nldr r0, _080475E4 @ =0x03000630\nldr r3, [r0, #0x00]\ncmp r3, #0x00\nbeq _080475E0\nldr r0, _080475E8 @ =0x03000198\nldr r1, [r0, #0x00]\nldr r0, _080475EC @ =0x00001798\nadds r2, r1, r0\nldr r0, [r3, #0x40]\nstr r0, [r2, #0x00]\nldr r0, _080475F0 @ =0x0000179C\nadds r1, r1, r0\nldr r0, [r3, #0x44]\nstr r0, [r1, #0x00]\n_080475E0:\nbx lr\n.byte 0x00, 0x00\n_080475E4: .4byte 0x03000630\n_080475E8: .4byte 0x03000198\n_080475EC: .4byte 0x00001798\n_080475F0: .4byte 0x0000179C");
}
