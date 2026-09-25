#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08044a8c
void sub_08044A8C(void) {
    s32 *temp_r0;
    s32 *temp_r5;
    void *temp_r1;

    (gMainWorkPtr)->unk185B = 0;
    (gMainWorkPtr)->unk185C = 1;
    temp_r5 = HeapAlloc(0x18);
    temp_r0 = HeapAlloc(0x1F60);
    temp_r1 = gMainWorkPtr;
    temp_r1->unk1688 = (s32) *temp_r5;
    temp_r1->unk168C = (s32) *temp_r0;
    sub_080674BC(0x40);
    VBlankIntrWait();
    sub_08071B4C();
    *(s16 *)0x04000208 = 0;
}

