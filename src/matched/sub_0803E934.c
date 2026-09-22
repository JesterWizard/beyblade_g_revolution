#include "global.h"

// @ 0x0803e934
void sub_0803E934(struct Unk2F520 *a)
{
    u8 value1;
    u8 value2;
    s32 value1_shifted;
    s32 value2_shifted;

    value1 = a->unk2D5;
    value2 = a->unk2FC;
    sub_08061BE8();
    _0803E9A4();
    value2_shifted = ((s32)value2 << 24) >> 23;
    BgMapSetPaletteBankRun((u16)(value2_shifted + 5), 0x0F, 4, 0x1A);
    BgMapSetPaletteBankRun((u16)(value2_shifted + 6), 0x0F, 4, 0x1A);
    value1_shifted = ((s32)value1 << 24) >> 23;
    BgMapSetPaletteBankRun((u16)(value1_shifted + 5), 0x0E, 4, 0x1A);
    BgMapSetPaletteBankRun((u16)(value1_shifted + 6), 0x0E, 4, 0x1A);
}

