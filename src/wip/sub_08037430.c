#include "global.h"

void sub_08037430(void)
{
    void *first;
    void *second;
    u8 *count_ptr;
    void *const *table;

    first = sub_0807309C(0x40);
    second = sub_0807309C(0x40);
    if ((gMainWorkPtr->unk1808 & 2) == 0)
    {
        count_ptr = &gBattleWork->unk133;
        if (*count_ptr > 3)
            sub_080735DC(3, second, 0x40);
        else
            sub_080735DC(*count_ptr, second, 0x40);
        table = (void *const *)0x08096ECC;
        sub_08073AEC(
            table[gMainWorkPtr->unk1818],
            first,
            second,
            0x23,
            0x40);
        sub_08061E8C(
            &gBattleWork->unk013C.fields.unk174,
            (const void *)0x080B72F3,
            (const void *)0x082BF600,
            0xB0,
            0x170);
        sub_08061EF8(
            &gBattleWork->unk013C.fields.unk174,
            first,
            0,
            0x28,
            0,
            0xC8,
            0);
    }
    sub_08073114(first);
    sub_08073114(second);
}
