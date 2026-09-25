/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

s32 GetPlayerKeyedWord(void *keyArg)
{
    u32 key;
    struct Unk40EF4 *table;
    struct Unk40EF4 *keyp;
    u8 *valBase;
    u32 off;
    u32 *vals;
    struct MainWork *mw;
    u8 index;
    s32 neg1;
    u32 word;

    key = (u32)keyArg;
    table = gData_0808B2E4;
    word = table->unk00;
    neg1 = -1;
    if (word == (u32)neg1)
        return 0;

    off = 0;
    keyp = table;
    valBase = (u8 *)table + 4;
    for (;;)
    {
        if (keyp->unk00 == key)
        {
            vals = *(u32 **)(valBase + off);
            mw = gMainWorkPtr;
            index = mw->unk1818;
            return (s32)*(u32 *)((u8 *)vals + (index << 2));
        }
        table = (struct Unk40EF4 *)((u8 *)table + 8);
        off += 8;
        keyp = (struct Unk40EF4 *)((u8 *)keyp + 8);
        word = table->unk00;
        neg1 = -1;
        if (word == (u32)neg1)
            break;
    }
    return 0;
}
