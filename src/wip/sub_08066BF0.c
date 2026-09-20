#include "global.h"

struct Unk66BF0Entry
{
    u8 filler_00[0x18];
    u16 unk18;
};

void sub_08066BF0(struct Unk66BC4 *arg0)
{
    struct Unk66BF0Entry **entries;
    const u16 *defVal;
    const u16 *altVal;
    const u16 *end;

    entries = (struct Unk66BF0Entry **)*arg0->unk230;
    defVal = (const u16 *)0x080BAFA6;
    altVal = (const u16 *)0x080BAF6A;
    end = (const u16 *)((const u8 *)defVal + 0x3A);

    do
    {
        if (*(u8 *)gUnk_030009A8 != 0)
            (*entries)->unk18 = *altVal;
        else
            (*entries)->unk18 = *defVal;

        defVal++;
        entries++;
        altVal++;
    } while (defVal <= end);
}
