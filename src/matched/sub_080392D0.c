#include "global.h"

// @ 0x080392d0
__attribute__((naked))
void sub_080392D0(void)
{
    asm(".syntax unified\npush {lr}\nldr r0, _080392F8 @ =0x03000290\nldr r2, [r0, #0x00]\nldr r1, _080392FC @ =0x00001F48\nadds r0, r2, r1\nldr r0, [r0, #0x00]\nasrs r0, r0, #0x08\nmovs r1, #0xF0\nnegs r1, r1\ncmp r0, r1\nble _08039304\nldr r1, _08039300 @ =0x00001F38\nadds r0, r2, r1\nmovs r1, #0x08\nnegs r1, r1\nmovs r2, #0x00\nbl sub_080620D4\nb _0803930C\n.byte 0x00, 0x00\n_080392F8: .4byte 0x03000290\n_080392FC: .4byte 0x00001F48\n_08039300: .4byte 0x00001F38\n_08039304:\nldr r1, _0803932C @ =0x00001F38\nadds r0, r2, r1\nbl sub_08062044\n_0803930C:\nldr r0, _08039330 @ =0x03000290\nldr r1, [r0, #0x00]\nmovs r2, #0xF9\nlsls r2, r2, #0x05\nadds r0, r1, r2\nldr r0, [r0, #0x00]\nasrs r0, r0, #0x08\ncmp r0, #0xEF\nbgt _08039334\nsubs r2, #0x10\nadds r0, r1, r2\nmovs r1, #0x08\nmovs r2, #0x00\nbl sub_080620D4\nb _0803933C\n_0803932C: .4byte 0x00001F38\n_08039330: .4byte 0x03000290\n_08039334:\nldr r2, _08039340 @ =0x00001F10\nadds r0, r1, r2\nbl sub_08062044\n_0803933C:\npop {r0}\nbx r0\n_08039340: .4byte 0x00001F10");
}
