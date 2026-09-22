#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080686f4
/* match-compiler: old_agbcc */
void sub_080686F4(struct Unk68798 *a, s32 b, s32 c, s32 d, s32 e)
{
    struct Unk68798Heap *hp;
    struct Unk68798Entry *slot;
    struct Unk68798Entry *entries;
    s32 i;
    s32 free;
    s32 count;

    if (a->unk74 == -1) {
        a->unk74 = 0;
        hp = BtlObjAlloc(0x40);
        if (hp == 0) {
            DebugMessage((void *)0x083A94D4);
            return;
        }
        a->unk7C = hp;
        a->unk78 = hp->unk00;
    }
    if (a->unk74 > 3) {
        free = -1;
        count = 0;
        i = 0;
        entries = a->unk78;
        for (; i < 4; i++) {
            if (entries[i].unk00 == 0) {
                if (free < 0)
                    free = i;
                count++;
            }
        }
        if (free == -1)
            slot = entries;
        else
            slot = &entries[free];
        if (count == 4) {
            a->unk74 = 0;
            slot = entries;
        }
    } else {
        slot = &a->unk78[a->unk74];
    }
    slot->unk08 = (void *)b;
    slot->unk00 = d;
    slot->unk04 = e;
    slot->unk0C = c;
    a->unk74++;
}

