/* match-compiler: old_agbcc */
#include "global.h"

s32 sub_0803E2AC(struct Unk3E328 *a)
{
    struct Unk3E328 *base;
    const u8 *table1;
    s32 index1;
    const u8 *table2;
    const u8 *table3;
    const u8 *entry1;
    const u8 *entry2;
    const u8 *entry3;
    s32 red;
    s32 green;
    s32 blue;

    base = a;
    if (base == 0)
        return 0;

    table1 = (const u8 *)0x0807BDB8;
    index1 = base->unk1E;
    index1 <<= 2;
    entry1 = table1 + index1;
    table2 = (const u8 *)0x0807BB80;
    entry2 = table2 + ((s32)(s8)base->unk20 << 2);
    red = entry2[0] + entry1[0];
    green = entry2[1] + entry1[1];
    blue = entry2[2] + entry1[2];
    table3 = (const u8 *)0x0807B6F0;
    entry3 = table3 + ((s32)base->unk1D << 2);
    red += entry3[0];
    green += entry3[1];
    blue += entry3[2];

    if (red > 8)
        return 0;
    if (green > 8)
        return 1;
    if (green > 5 && blue > 5)
        return 2;
    return 3;
}
