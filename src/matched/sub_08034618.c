#include "global.h"

// @ 0x08034618
__attribute__((naked))
void sub_08034618(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nadds r5, r0, #0x0\nmovs r1, #0xAF\nlsls r1, r1, #0x02\nadds r0, r5, r1\nmovs r2, #0xAE\nlsls r2, r2, #0x02\nadds r1, r5, r2\nldr r0, [r0, #0x00]\nldr r1, [r1, #0x00]\ncmp r0, r1\nbeq _080346A0\nadds r2, #0x08\nadds r0, r5, r2\nldr r4, [r0, #0x00]\nlsls r0, r1, #0x10\nadds r2, #0x34\nadds r1, r5, r2\nldr r1, [r1, #0x00]\nlsls r1, r1, #0x08\nbl _080740B0\nlsls r1, r0, #0x01\nadds r1, r1, r0\nlsls r1, r1, #0x03\nadds r1, r1, r0\nlsls r1, r1, #0x0A\nasrs r1, r1, #0x10\nadds r4, r4, r1\nmovs r0, #0x01\nbl sub_0802C62C\ncmp r0, #0x01\nbgt _08034670\nmovs r1, #0xC3\nlsls r1, r1, #0x02\nadds r0, r5, r1\nldrb r0, [r0, #0x00]\ncmp r0, #0x00\nbne _08034670\nasrs r4, r4, #0x01\ncmp r4, #0x31\nble _08034670\nmovs r4, #0x32\n_08034670:\ncmp r4, #0x63\nble _08034680\nmovs r4, #0x64\nmovs r2, #0xB1\nlsls r2, r2, #0x02\nadds r1, r5, r2\nmovs r0, #0x01\nb _08034688\n_08034680:\nmovs r0, #0xB1\nlsls r0, r0, #0x02\nadds r1, r5, r0\nmovs r0, #0x00\n_08034688:\nstrb r0, [r1, #0x00]\nldr r0, [r5, #0x04]\nldr r0, [r0, #0x28]\nadds r0, #0x24\nstrb r4, [r0, #0x00]\nmovs r2, #0xAF\nlsls r2, r2, #0x02\nadds r1, r5, r2\nsubs r2, #0x04\nadds r0, r5, r2\nldr r0, [r0, #0x00]\nstr r0, [r1, #0x00]\n_080346A0:\npop {r4, r5}\npop {r0}\nbx r0");
}
