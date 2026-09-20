#include "global.h"

void sub_08052934(s32 arg0)
{
    u32 idx = (u8)arg0 << 4;
    void **arr;

    sub_080615EC(0, idx + 8);
    sub_080617C4((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    arr = *(void ***)(0x080995AC + 0xC + idx);
    sub_0806171C(arr[gMainWorkPtr->unk1818], 0x24, 2);
}
