#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08043b58
/* match-compiler: old_agbcc */
struct Unk447CC *sub_08043B58(void)
{
    u32 key = gMainWorkPtr->unk1690->unk00;
    struct Unk447CC *p = *gData_08096794;
    struct Unk447CC **walk;

    if (p != 0)
    {
        walk = gData_08096794 + 1;
        do
        {
            if (key == (u32)p->unk00)
                return p;
            p = *walk++;
        } while (p != 0);
    }
    return 0;
}
