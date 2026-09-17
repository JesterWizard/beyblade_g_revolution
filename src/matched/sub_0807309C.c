#include "global.h"

// @ 0x0807309c
__attribute__((naked))
void sub_0807309C(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nadds r7, r0, #0x0\nmovs r6, #0x00\nldr r0, _08073100 @ =0x03004150\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _0807310C\nadds r5, r0, #0x0\nmovs r4, #0x00\nldr r0, _08073104 @ =0x03004154\nldrb r1, [r0, #0x00]\nadds r3, r0, #0x0\ncmp r6, r1\nbcs _080730D0\nldr r0, [r5, #0x00]\ncmp r0, #0x00\nbeq _080730D0\nadds r2, r1, #0x0\nadds r1, r5, #0x0\n_080730C2:\nadds r1, #0x04\nadds r4, #0x01\ncmp r4, r2\nbcs _080730D0\nldr r0, [r1, #0x00]\ncmp r0, #0x00\nbne _080730C2\n_080730D0:\nldrb r3, [r3, #0x00]\ncmp r4, r3\nbeq _0807310C\nadds r0, r7, #0x0\nbl sub_0806A3A4\nadds r1, r0, #0x0\nlsls r0, r4, #0x02\nadds r0, r0, r5\nstr r1, [r0, #0x00]\ncmp r1, #0x00\nbeq _0807310C\nldr r6, [r1, #0x00]\nadds r0, r6, #0x0\nadds r1, r7, #0x0\nbl sub_08073184\nldr r1, _08073108 @ =0x03004158\nldrb r0, [r1, #0x00]\nadds r0, #0x01\nstrb r0, [r1, #0x00]\nadds r0, r6, #0x0\nb _0807310E\n.byte 0x00, 0x00\n_08073100: .4byte 0x03004150\n_08073104: .4byte 0x03004154\n_08073108: .4byte 0x03004158\n_0807310C:\nmovs r0, #0x00\n_0807310E:\npop {r4, r5, r6, r7}\npop {r1}\nbx r1");
}
