#include "global.h"

// @ 0x08033084
__attribute__((naked))
void sub_08033084(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nadds r5, r0, #0x0\nlsls r1, r1, #0x18\ncmp r1, #0x00\nbeq _080330D0\nldr r4, _080330D8 @ =0x03000290\nldr r3, [r4, #0x00]\nldr r0, _080330DC @ =0x00001F94\nadds r2, r3, r0\nsubs r0, #0x04\nadds r1, r3, r0\nldr r0, [r2, #0x00]\nldr r1, [r1, #0x00]\nadds r0, r0, r1\nstr r0, [r2, #0x00]\nadds r2, r0, #0x0\nldr r0, _080330E0 @ =0x000007FF\ncmp r2, r0\nble _080330B6\nmovs r2, #0x80\nlsls r2, r2, #0x04\nldr r0, _080330E4 @ =0x00001F98\nadds r1, r3, r0\nmovs r0, #0x00\nstrb r0, [r1, #0x00]\n_080330B6:\ncmp r2, #0x00\nbgt _080330C4\nmovs r2, #0x00\nldr r0, [r4, #0x00]\nldr r1, _080330E4 @ =0x00001F98\nadds r0, r0, r1\nstrb r2, [r0, #0x00]\n_080330C4:\nmovs r1, #0xA0\nlsls r1, r1, #0x13\nasrs r2, r2, #0x08\nadds r0, r5, #0x0\nbl sub_080726E0\n_080330D0:\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_080330D8: .4byte 0x03000290\n_080330DC: .4byte 0x00001F94\n_080330E0: .4byte 0x000007FF\n_080330E4: .4byte 0x00001F98");
}
