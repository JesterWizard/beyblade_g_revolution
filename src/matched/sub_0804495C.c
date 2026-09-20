#include "global.h"

// @ 0x0804495c
__attribute__((naked))
void sub_0804495C(void)
{
    asm(".syntax unified\nldr r1, _08044988 @ =0x08094E00\nldr r0, _0804498C @ =0x03000198\nldr r0, [r0, #0x00]\nldr r2, _08044990 @ =0x0000181F\nadds r0, r0, r2\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r1, [r0, #0x00]\nldr r3, _08044994 @ =0x050001C0\nmovs r2, #0x1F\n_08044976:\nldrh r0, [r1, #0x00]\nstrh r0, [r3, #0x00]\nadds r1, #0x02\nadds r3, #0x02\nsubs r2, #0x01\ncmp r2, #0x00\nbge _08044976\nbx lr\n.byte 0x00, 0x00\n_08044988: .4byte 0x08094E00\n_0804498C: .4byte 0x03000198\n_08044990: .4byte 0x0000181F\n_08044994: .4byte 0x050001C0");
}
