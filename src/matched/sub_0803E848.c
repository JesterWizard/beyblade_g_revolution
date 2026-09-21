#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803e848
#include "global.h"

void sub_0803E848(struct Unk2F520 *a, s32 b, void *c)
{
    s32 offset;
    s32 first_y;
    void *table;
    void *out;

    out = c;
    if (b == (s8)a->unk2D5)
        sub_08061610(0x0E);
    else
        sub_08061610(0x0F);

    sub_080617C4((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    offset = b << 4;
    first_y = offset + 8;
    sub_080615EC(0, first_y);
    table = (void *)0x0833D408;
    sub_0806171C(table, (u32)(sub_08061784() << 16) >> 17, 0);
    offset += 0x10;
    sub_080615EC(0, offset);
    sub_0806171C(table, (u32)(sub_08061784() << 16) >> 17, 0);
    sub_080617C4((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    sub_080615EC(0, first_y);
    sub_0806171C(out, 0x23, 2);
}

