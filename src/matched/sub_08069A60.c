#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x08069a60
/* match-compiler: old_agbcc */
// Sets the rotation/scale matrix for affine BG `bg` (2 or 3): stores the angle
// and scale indices in its slot, builds PA..PD from the sine table and the
// reciprocal scale table, and writes them to the BG's affine registers.
void sub_08069A60(u8 bg, u8 angle, u16 scaleX, u16 scaleY)
{
    struct Unk0068Entry *e;
    u8 slot = bg - 2;

    if (slot > 2)
        return;
    gData_03000068[slot].unk02 = scaleX;
    gData_03000068[slot].unk04 = scaleY;
    gData_03000068[slot].unk00 = angle;
    e = &gData_03000068[slot];
    gData_03000068[slot].unk08 = (s16)sub_08069F00(gData_083C9544[angle + 0x40], gData_083A9544[e->unk02]);
    gData_03000068[slot].unk0C = (s16)sub_08069F00(gData_083C9544[e->unk00], gData_083A9544[e->unk02]);
    gData_03000068[slot].unk10 = (s16)sub_08069F00(-gData_083C9544[e->unk00], gData_083A9544[e->unk04]);
    gData_03000068[slot].unk14 = (s16)sub_08069F00(gData_083C9544[e->unk00 + 0x40], gData_083A9544[e->unk04]);
    BgAffineSetMatrix(bg, gData_03000068[slot].unk08, gData_03000068[slot].unk0C, gData_03000068[slot].unk10, gData_03000068[slot].unk14);
}

