#include "global.h"

// @ 0x0803E328
s32 sub_0803E328(struct Unk3E328 *a)
{
    const u8 *table2;
    const u8 *table3;
    const u8 *entry1;
    s32 value;

    table2 = (const u8 *)0x0807BB80;
    table3 = (const u8 *)0x0807B6F0;
    entry1 = (const u8 *)0x0807BDB8 + ((s32)a->unk1E << 2);
    value = table2[((s32)(s8)a->unk20) << 2] + *entry1;
    value += table3[((s32)a->unk1D) << 2];
    return _080741EC(value, 3) - 1;
}
