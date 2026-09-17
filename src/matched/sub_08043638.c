#include "global.h"

// @ 0x08043638
__attribute__((naked))
void sub_08043638(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r5, _08043684 @ =0x03000198\nldr r0, [r5, #0x00]\nldr r1, _08043688 @ =0x00000868\nadds r2, r0, r1\nmovs r3, #0xDC\nlsls r3, r3, #0x02\nadds r1, r0, r3\nldr r1, [r1, #0x00]\nstr r1, [r2, #0x00]\nldr r1, _0804368C @ =0x0000086C\nadds r2, r0, r1\nadds r3, #0x04\nadds r1, r0, r3\nldr r1, [r1, #0x00]\nstr r1, [r2, #0x00]\nldr r1, _08043690 @ =0x0000039D\nadds r0, r0, r1\nmovs r2, #0x00\nstrb r2, [r0, #0x00]\nldr r0, [r5, #0x00]\nldr r3, _08043694 @ =0x00001810\nadds r0, r0, r3\nmovs r1, #0x80\nlsls r1, r1, #0x01\nstr r1, [r0, #0x00]\nldr r4, _08043698 @ =0x03000554\nldr r0, [r4, #0x00]\nstrb r2, [r0, #0x01]\nbl sub_080436B0\nldr r0, [r4, #0x00]\nldrb r0, [r0, #0x01]\ncmp r0, #0x01\nbne _0804369C\nbl sub_08043420\nb _080436AA\n_08043684: .4byte 0x03000198\n_08043688: .4byte 0x00000868\n_0804368C: .4byte 0x0000086C\n_08043690: .4byte 0x0000039D\n_08043694: .4byte 0x00001810\n_08043698: .4byte 0x03000554\n_0804369C:\nldr r0, [r5, #0x00]\nmovs r1, #0xDB\nlsls r1, r1, #0x02\nadds r0, r0, r1\nmovs r1, #0x07\nbl sub_080680CC\n_080436AA:\npop {r4, r5}\npop {r0}\nbx r0");
}
