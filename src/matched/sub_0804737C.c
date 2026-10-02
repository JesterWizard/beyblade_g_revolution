#include "global.h"

// @ 0x0804737c
void sub_0804737C(void)
{
    u8 idx;

    sub_080400C0(-1);
    idx = SaveSlotGet();
    sub_08045128(idx);
    sub_080628E4(gMainWorkPtr->unk170C * gMainWorkPtr->unk1788 + (s32)0xFC96FCDE);
    BgmSetVolume(gMainWorkPtr->bgmVolume);
    BtlSetAllUnk1710(gMainWorkPtr->sfxVolume);
    SparklesRestoreTimers();
}
