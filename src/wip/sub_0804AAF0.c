#include "global.h"

void sub_0804AAF0(void)
{
    void *buffer;
    struct Unk4AAF0 *entry;
    struct Unk4AAF0 **current_loc;

    buffer = sub_0807309C(0x10);
    current_loc = &gUnk_03000660;
    entry = gUnk_03000658[gUnk_03000654];
    *current_loc = entry;

    sub_080615EC(0, 0x18);
    sub_0806171C((void *)sub_0803EBB0((s8)gUnk_03000660->unk1D), 0xC4, 1);
    sub_080615EC(0, 0x20);
    sub_0806171C((void *)sub_0803ECB8((s8)gUnk_03000660->unk1E), 0xC4, 1);
    sub_080615EC(0, 0x28);
    sub_0806171C((void *)sub_0803EC34((s8)gUnk_03000660->unk20), 0xC4, 1);

    sub_080615EC(0, 0x30);
    if ((gUnk_03000660->unk1F & 0x40) != 0)
        sub_0806171C((void *)0x083A74F0, 0xC4, 1);
    else
        sub_0806171C((void *)0x083A74FC, 0xC4, 1);

    sub_080615EC(0, 0x38);
    if (gUnk_03000660->unk21 == -1)
        sub_0806171C((void *)0x083A7508, 0xC4, 1);
    else
        sub_0806171C(
            (void *)sub_0803DBD0(gUnk_03000660->unk21),
            0xC4,
            1);

    sub_080735DC(gUnk_03000660->unk26, buffer, 0x10);
    sub_080615EC(0, 0x40);
    sub_0806171C(buffer, 0xC4, 1);
    sub_080615EC(0, 0x48);
    sub_0806171C(
        (void *)sub_0803DD60(gUnk_03000660->unk1F & 3),
        0xC4,
        1);
    sub_08073114(buffer);
}
