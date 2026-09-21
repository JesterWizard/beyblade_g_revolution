#include "global.h"
#include "ram_map.h"

// @ 0x08043b90
// 67/76 same-size (88.2%). Structure matches retail exactly (entry `p == 0 ->
// return -1`, bottom-test `while (p->unk00 != 0)`, body `call == 0 -> return
// p->unk04`, `p++`). Two remaining DIFFs, both from `return 0` at the end:
// agbcc emits `movs r0,#0` while retail falls through with r0 already 0 from the
// loop's last load, which shifts two branch offsets by 2 bytes. Needs the tail
// value to reuse the loaded p->unk00.
s32 sub_08043B90(void)
{
    struct Unk43B90 *p = *(struct Unk43B90 **)((u8 *)gMainWorkPtr + 0x16E0);

    if (p == 0)
        return -1;
    while (p->unk00 != 0)
    {
        if (sub_08073440(p->unk00, (void *)*(u32 *)((u8 *)gMainWorkPtr + 0x16C8)) == 0)
            return p->unk04;
        p++;
    }
    return 0;
}
