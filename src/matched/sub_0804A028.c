#include "global.h"

// @ 0x0804a028
__attribute__((naked))
void sub_0804A028(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r2, _0804A078 @ =0x000002D5\nadds r1, r0, r2\nldrb r5, [r1, #0x00]\nmovs r1, #0xBF\nlsls r1, r1, #0x02\nadds r0, r0, r1\nldrb r4, [r0, #0x00]\nldr r0, _0804A07C @ =0x03000198\nldr r0, [r0, #0x00]\nldr r2, _0804A080 @ =0x00001855\nadds r0, r0, r2\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\ncmp r0, #0x00\nbeq _0804A084\nlsls r0, r4, #0x18\nasrs r0, r0, #0x08\nmovs r1, #0xA0\nlsls r1, r1, #0x0B\nadds r0, r0, r1\nlsrs r0, r0, #0x10\nmovs r1, #0x0F\nmovs r2, #0x09\nmovs r3, #0x14\nbl sub_08061D68\nlsls r0, r5, #0x18\nasrs r0, r0, #0x08\nmovs r2, #0xA0\nlsls r2, r2, #0x0B\nadds r0, r0, r2\nlsrs r0, r0, #0x10\nmovs r1, #0x0E\nmovs r2, #0x09\nmovs r3, #0x14\nbl sub_08061D68\nb _0804A0D0\n_0804A078: .4byte 0x000002D5\n_0804A07C: .4byte 0x03000198\n_0804A080: .4byte 0x00001855\n_0804A084:\nlsls r4, r4, #0x18\nasrs r4, r4, #0x17\nadds r0, r4, #0x5\nlsls r0, r0, #0x10\nlsrs r0, r0, #0x10\nmovs r1, #0x0F\nmovs r2, #0x09\nmovs r3, #0x14\nbl sub_08061D68\nadds r4, #0x06\nlsls r4, r4, #0x10\nlsrs r4, r4, #0x10\nadds r0, r4, #0x0\nmovs r1, #0x0F\nmovs r2, #0x09\nmovs r3, #0x14\nbl sub_08061D68\nlsls r4, r5, #0x18\nasrs r4, r4, #0x17\nadds r0, r4, #0x5\nlsls r0, r0, #0x10\nlsrs r0, r0, #0x10\nmovs r1, #0x0E\nmovs r2, #0x09\nmovs r3, #0x14\nbl sub_08061D68\nadds r4, #0x06\nlsls r4, r4, #0x10\nlsrs r4, r4, #0x10\nadds r0, r4, #0x0\nmovs r1, #0x0E\nmovs r2, #0x09\nmovs r3, #0x14\nbl sub_08061D68\n_0804A0D0:\npop {r4, r5}\npop {r0}\nbx r0");
}
