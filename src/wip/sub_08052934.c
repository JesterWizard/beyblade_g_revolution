#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08052934
void sub_08052934(u32 a)
{
    u32 idx = a << 24;
    u32 off;
    u8 *id;
    void **table;

    idx >>= 20;
    sub_080615EC(0, idx + 8);
    sub_080617C4((struct Unk617C4 *)gData_082BCD00, (u32)gData_080B738E);
    off = (u32)gData_080995AC;
    off += 0xC;
    idx += off;
    id = &gMainWorkPtr->unk1818;
    table = *(void ***)idx;
    sub_0806171C(table[*id], 0x24, 2);
}
