#include "global.h"

void sub_0804AAF0(void)
{
    void *buffer;
    struct Unk4AAF0 *entry;
    struct Unk4AAF0 **current_loc;

    buffer = BtlObjTableAdd(0x10);
    current_loc = &gUnk_03000660;
    entry = gUnk_03000658[gUnk_03000654];
    *current_loc = entry;

    TextSetCursor(0, 0x18);
    TextDrawAlign((void *)sub_0803EBB0((s8)gUnk_03000660->unk1D), 0xC4, 1);
    TextSetCursor(0, 0x20);
    TextDrawAlign((void *)sub_0803ECB8((s8)gUnk_03000660->unk1E), 0xC4, 1);
    TextSetCursor(0, 0x28);
    TextDrawAlign((void *)sub_0803EC34((s8)gUnk_03000660->unk20), 0xC4, 1);

    TextSetCursor(0, 0x30);
    if ((gUnk_03000660->unk1F & 0x40) != 0)
        TextDrawAlign((void *)0x083A74F0, 0xC4, 1);
    else
        TextDrawAlign((void *)0x083A74FC, 0xC4, 1);

    TextSetCursor(0, 0x38);
    if (gUnk_03000660->unk21 == -1)
        TextDrawAlign((void *)0x083A7508, 0xC4, 1);
    else
        TextDrawAlign(
            (void *)sub_0803DBD0(gUnk_03000660->unk21),
            0xC4,
            1);

    TextFormatInt(gUnk_03000660->unk26, buffer, 0x10);
    TextSetCursor(0, 0x40);
    TextDrawAlign(buffer, 0xC4, 1);
    TextSetCursor(0, 0x48);
    TextDrawAlign(
        (void *)sub_0803DD60(gUnk_03000660->unk1F & 3),
        0xC4,
        1);
    BtlObjTableRemove(buffer);
}
