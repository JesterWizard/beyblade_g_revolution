#include "global.h"

// @ 0x08031204
__attribute__((naked))
void sub_08031204(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nmovs r0, #0x10\nbl sub_0807309C\nadds r5, r0, #0x0\nldr r0, _08031280 @ =0x030002A0\nldr r0, [r0, #0x0C]\nldr r4, _08031284 @ =0x03000290\nldr r1, [r4, #0x00]\nldr r2, _08031288 @ =0x00000BB4\nadds r1, r1, r2\nldr r1, [r1, #0x00]\nmovs r2, #0x80\nbl sub_08031124\nlsls r0, r0, #0x10\nasrs r2, r0, #0x10\nmovs r0, #0x01\nnegs r0, r0\ncmp r2, r0\nbeq _08031242\nldr r0, [r4, #0x00]\nmovs r1, #0xAF\nlsls r1, r1, #0x04\nadds r0, r0, r1\nldr r1, [r0, #0x00]\ncmp r1, #0x00\nbeq _08031242\nmovs r0, #0x80\nsubs r0, r0, r2\nstrh r0, [r1, #0x18]\n_08031242:\nldr r0, _08031280 @ =0x030002A0\nldr r0, [r0, #0x38]\nldr r4, _08031284 @ =0x03000290\nldr r1, [r4, #0x00]\nldr r2, _0803128C @ =0x00000BB8\nadds r1, r1, r2\nldr r1, [r1, #0x00]\nmovs r2, #0x80\nbl sub_08031124\nlsls r0, r0, #0x10\nasrs r2, r0, #0x10\nmovs r0, #0x01\nnegs r0, r0\ncmp r2, r0\nbeq _08031274\nldr r0, [r4, #0x00]\nldr r1, _08031290 @ =0x00000AF4\nadds r0, r0, r1\nldr r1, [r0, #0x00]\ncmp r1, #0x00\nbeq _08031274\nmovs r0, #0x80\nsubs r0, r0, r2\nstrh r0, [r1, #0x18]\n_08031274:\nadds r0, r5, #0x0\nbl sub_08073114\npop {r4, r5}\npop {r0}\nbx r0\n_08031280: .4byte 0x030002A0\n_08031284: .4byte 0x03000290\n_08031288: .4byte 0x00000BB4\n_0803128C: .4byte 0x00000BB8\n_08031290: .4byte 0x00000AF4");
}
