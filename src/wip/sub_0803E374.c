#include "global.h"

// @ 0x0803E374
s32 sub_0803E374(struct Unk3E328 *a)
{
    register const u8 *table1;
    register s32 index1;
    const u8 *table2;
    const u8 *table3;
    const u8 *entry1;
    s32 value;

    table1 = (const u8 *)0x0807BDB8;
    table2 = (const u8 *)0x0807BB80;
    table3 = (const u8 *)0x0807B6F0;
    index1 = a->unk1E;
    index1 <<= 2;
    entry1 = table1 + index1;
    value = table2[(((s32)(s8)a->unk20) << 2) + 1] + entry1[1];
    value += table3[(((s32)a->unk1D) << 2) + 1];
    return _080741EC(value, 3) - 1;
}
