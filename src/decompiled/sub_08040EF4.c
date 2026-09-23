#include "global.h"
#include "ram_map.h"

// @ 0x08040EF4
// Keyed lookup in the 8-byte ROM table at 0x0808B2E4 (rows end at key 0xFFFFFFFF).
// On hit, returns the gMainWorkPtr->unk1818-th u32 from the row's value pointer.
s32 sub_08040EF4(void *key)
{
    struct Unk40EF4 *entry;
    u32 searchKey;
    u8 index;

    searchKey = (u32)key;
    entry = (struct Unk40EF4 *)0x0808B2E4;
    if (entry->unk00 == (u32)-1)
        return 0;

    index = gMainWorkPtr->unk1818;
    do
    {
        if (entry->unk00 == searchKey)
            return (s32)((u32 *)entry->unk04)[index];
        entry++;
    }
    while (entry->unk00 != (u32)-1);

    return 0;
}
