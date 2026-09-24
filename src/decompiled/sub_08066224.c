/* match-compiler: old_agbcc */
#include "global.h"

void sub_08066224(struct Unk66224 *a, s32 index)
{
    struct Unk66224 *obj;
    s32 cur;
    s32 scaled;
    u32 table;
    struct Unk66224Entry *current;
    struct Unk66224Entry *entry;
    struct Unk66224Object *entryObj;
    struct Unk7069C *state;
    s32 lookup;
    u32 ptr;

    obj = a;
    cur = obj->unk04;
    scaled = (cur << 3) - cur;
    scaled <<= 2;
    table = (u32)obj->unk28;
    current = (struct Unk66224Entry *)(table + scaled);
    if (index < 0)
        return;
    if (index >= obj->unk00)
        return;
    if ((1 & obj->unk3C) != 0)
        return;
    scaled = (index << 3) - index;
    scaled <<= 2;
    entry = (struct Unk66224Entry *)(scaled + table);
    current->unk14 = current->unk00->unk20;
    entryObj = entry->unk00;
    entry->unk14 = entryObj->unk24;
    obj->unk14 = 0xFFFF - index * obj->unk0C;
    obj->unk04 = index;
    state = &obj->unk40;
    lookup = GetBtlLookupByte();
    lookup <<= 2;
    ptr = (u32)entryObj + 4;
    ptr += lookup;
    sub_08070AD4(state, *(void **)ptr, obj->unk2C->unk00->unk0A);
}
