#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806be20
/* match-compiler: old_agbcc */
// Index into a size-prefixed entry table: entry = base + 4, then walk `c`
// entries by adding the u16 length stored at the head of each entry.
// Declaration order matters here: agbcc emits `i = 0` before `p = b + 4` only
// when `i` is declared/initialised first (retail: movs r3,#0; adds r0,r1,#4).
void *sub_0806BE20(void *a, void *b, s32 c)
{
    s32 i = 0;
    u8 *p = (u8 *)b + 4;

    if (b == 0 || c >= (s32)*(u16 *)b)
        return 0;
    if (i < c)
    {
        i = c;
        do
        {
            p = p + *(u16 *)p;
            i--;
        } while (i != 0);
    }
    return p;
}

