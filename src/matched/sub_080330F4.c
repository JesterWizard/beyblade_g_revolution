#include "global.h"

// @ 0x080330f4
__attribute__((naked))
void sub_080330F4(void)
{
    asm(".syntax unified\npush {r4, lr}\nldr r3, _08033118 @ =0x03000290\nldr r1, [r3, #0x00]\nldr r4, _0803311C @ =0x00001F90\nadds r2, r1, r4\nstr r0, [r2, #0x00]\nldr r2, _08033120 @ =0x00001F98\nadds r1, r1, r2\nmovs r2, #0x01\nstrb r2, [r1, #0x00]\ncmp r0, #0x00\nblt _08033124\nldr r0, [r3, #0x00]\nadds r4, #0x04\nadds r0, r0, r4\nmovs r1, #0x00\nb _0803312E\n.byte 0x00, 0x00\n_08033118: .4byte 0x03000290\n_0803311C: .4byte 0x00001F90\n_08033120: .4byte 0x00001F98\n_08033124:\nldr r0, [r3, #0x00]\nldr r1, _08033138 @ =0x00001F94\nadds r0, r0, r1\nmovs r1, #0x80\nlsls r1, r1, #0x04\n_0803312E:\nstr r1, [r0, #0x00]\npop {r4}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08033138: .4byte 0x00001F94");
}
