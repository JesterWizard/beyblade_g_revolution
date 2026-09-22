/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803dd88
// MATCHED -> src/matched/sub_0803DD88.c (old_agbcc)
// Row lookup into the 40-byte-stride table at gData_0807A1F4, indexed by the u8
// at gMainWorkPtr+0x1818. `off` must be a separate local and old_agbcc is
// required: that combination gives retail's `ldrb r1,[r1]` / `lsls r2,r1,#2`
// index handling instead of the default agbcc allocation.
s32 sub_0803DD88(s32 a)
{
    u8 *base = gData_0807A1F4;
    u32 off = gMainWorkPtr->unk1818 * 4 + a * 40;

    return *(s32 *)(base + off);
}
