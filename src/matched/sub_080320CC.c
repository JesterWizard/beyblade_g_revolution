#include "global.h"

// @ 0x080320cc
__attribute__((naked))
void sub_080320CC(void)
{
    asm(".syntax unified\nldr r1, _080320FC @ =0x030002A0\nldr r0, [r1, #0x0C]\ncmp r0, #0x00\nbge _080320D8\nmovs r0, #0x00\nstr r0, [r1, #0x0C]\n_080320D8:\nldr r0, [r1, #0x38]\ncmp r0, #0x00\nbge _080320E2\nmovs r0, #0x00\nstr r0, [r1, #0x38]\n_080320E2:\nldr r0, [r1, #0x64]\ncmp r0, #0x00\nbge _080320EC\nmovs r0, #0x00\nstr r0, [r1, #0x64]\n_080320EC:\nadds r1, #0x90\nldr r0, [r1, #0x00]\ncmp r0, #0x00\nbge _080320F8\nmovs r0, #0x00\nstr r0, [r1, #0x00]\n_080320F8:\nbx lr\n.byte 0x00, 0x00\n_080320FC: .4byte 0x030002A0");
}
