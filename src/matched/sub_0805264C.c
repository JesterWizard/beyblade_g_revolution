#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0805264c
void sub_0805264C(struct Unk2F520 *a, u32 idx)
{
    u32 off;
    u32 scaled;
    void *fn;
    s32 field;
    u32 row;
    u16 n;

    off = (u32)gData_080995AC;
    scaled = idx << 4;
    off += 8;
    fn = *(void **)(off + scaled);
    if (fn != 0)
        _08073C48(a, (void *)idx, fn);
    field = a->unk2D5;
    row = 0x0F;
    if (idx == (u32)field)
        row = 0x0E;
    n = (idx << 1) + 5;
    sub_08061D68(n, row, 4, 0x19);
    n = (idx << 1) + 6;
    sub_08061D68(n, row, 4, 0x19);
}
