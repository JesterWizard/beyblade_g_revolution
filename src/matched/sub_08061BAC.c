#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061bac
#include "global.h"

// @ 0x08061bac
void sub_08061BAC(void)
{
    struct Unk0770 *p;
    s32 n;
    void *z;

    p = (struct Unk0770 *)gUnk_03000770;
    z = 0;
    n = 3;
    do
    {
        if (p->unk00 != 0)
        {
            BtlObjFree(p->unk00);
            p->unk00 = z;
        }
        p++;
        n--;
    } while (n >= 0);
    gUnk_03000794 = 0;
}

