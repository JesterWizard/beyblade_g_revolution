#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08033188
void sub_08033188(void) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 spA4;
    s32 spA8;
    s32 spAC;
    s32 spB0;
    s32 *spB4;
    s32 *spB8;
    s32 *spBC;
    s32 *spC0;
    s32 *spC4;
    s32 *temp_r0;

    spA4 = (s32) *(u16 *)gBtlInputMask;
    spA8 = (s32) *(u16 *)gUnk_03004064;
    spAC = (s32) gBtlKeysHeldU16;
    spB0 = (s32) *(u16 *)gBtlKeysNew;
    sp0 = 0x50;
    sp4 = 0xF0;
    sp8 = 2;
    sub_08070604(&spC, 0x082BF600, 0x080B72F3, -0xF0);
    sub_08070AD4(&spC, *(0x080780EC + ((gMainWorkPtr)->unk1818 * 4)), 0);
    sub_0807179C(&spC);
    sub_080312EC((s32)gBattleWork + 0xB84);
    sub_080312EC((s32)gBattleWork + 0xB94);
    sub_0803484C((s32)gBattleWork + 0x478);
    sub_0803484C((s32)gBattleWork + 0x790);
    temp_r0 = &sp0 + 0x74;
    spB4 = temp_r0;
    spB8 = &sp0 + 0x78;
    spBC = &sp0 + 0x7C;
    spC0 = &sp0 + 0x80;
    spC4 = temp_r0 + 0x14;
}

