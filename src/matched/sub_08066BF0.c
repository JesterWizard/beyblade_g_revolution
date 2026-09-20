#include "global.h"

// @ 0x08066bf0
#include "global.h"

struct Unk66BF0Entry
{
    u8 filler_00[0x18];
    u16 unk18;
};

void sub_08066BF0(struct Unk66BC4 *arg0)
{
    struct Unk66BF0Entry ***entriesSlot;
    register struct Unk66BF0Entry **entries;
    register const u16 *defVal;
    register const u16 *altVal;
    register const u8 *flagPtr;
    register const u16 *end;

    entriesSlot = (struct Unk66BF0Entry ***)arg0->unk230;
    flagPtr = (const u8 *)0x030009A8;
    defVal = (const u16 *)0x080BAFA6;
    entries = *entriesSlot;
    altVal = (const u16 *)0x080BAF6A;
    end = (const u16 *)((const u8 *)defVal + 0x3A);

    do
    {
        if (*flagPtr != 0)
            (*entries)->unk18 = *altVal;
        else
            (*entries)->unk18 = *defVal;

        defVal++;
        entries++;
        altVal++;
    } while ((s32)defVal <= (s32)end);
}

