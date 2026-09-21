#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08031294
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08031294
// Set both byte flags to all-ones, then publish -1 in the +0x04 word and clear the
// +0x0C word / +0x08 byte. The two ORs must be written out inline with an explicit
// (u8) cast: a `u8 m = 0xFF;` local makes agbcc emit the `ldrb`/`orrs` pair in the
// opposite register order (5/28, and it adds a spurious stack frame).
void sub_08031294(struct Unk312EC *a)
{
    a->unk00 = (s8)((u8)a->unk00 | 0xFF);
    a->unk01 = (s8)((u8)a->unk01 | 0xFF);
    a->unk04 = -1;
    a->unk0C = 0;
    a->unk08 = 0;
}

