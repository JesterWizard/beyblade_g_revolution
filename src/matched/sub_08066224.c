#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08066224
/* match-compiler: old_agbcc */
#include "global.h"

void sub_08066224(struct Unk66224 *a, s32 index)
{
    struct Unk66224 *obj;
    struct Unk66224Entry *alias;
    s32 cur;
    s32 scaled;
    u32 table;
    struct Unk66224Entry *current;
    struct Unk66224Entry *entry;
    struct Unk66224Object *entryObj;
    struct Unk7069C *state;
    s32 *scaledp;
    s32 lookup;
    s32 *unk0Cp;
    u32 ptr;

    obj = a;
    cur = obj->unk04;
    scaled = (cur << 3) - cur;
    scaled <<= 2;
    scaledp = &scaled;
    table = (u32)obj->unk28;
    current = (struct Unk66224Entry *)(table + (*scaledp));
    if (index < 0)
        return;
    if (index >= obj->unk00)
        return;
    if ((1 & obj->unk3C) != 0)
        return;
    scaled = (index << 3) - index;
    scaled <<= 2;
    entry = (struct Unk66224Entry *)(table + scaled);
    alias = current;
    current->unk14 = alias->unk00->unk20;
    entryObj = entry->unk00;
    unk0Cp = &obj->unk0C;
    entry->unk14 = entryObj->unk24;
    obj->unk14 = 0xFFFF - (index * (*unk0Cp));
    obj->unk04 = index;
    state = &obj->unk40;
    lookup = sub_08072F94();
    lookup <<= 2;
    ptr = ((u32)entryObj) + 4;
    ptr += lookup;
    sub_08070AD4(state, *((void **)ptr), obj->unk2C->unk00->unk0A);
}

