#include "global.h"
#include "ram_map.h"
#include "battle.h"

extern void sub_080428C4(void);

// @ 0x080428f0
/* match-compiler: old_agbcc */
void sub_080428F0(u32 a, u32 b, u32 c, u32 d)
{
    struct Unk0538 *ring;
    s32 i;

    if (gMainWorkPtr->unk1808 & 0x4000)
        return;
    sub_080428C4();
    i = 0;
    do
    {
        ring = gUnk_03000538;
        ring->unk04[i] = (u16)d;
        ring->unk44[i] = a;
        ring->unkC4[i] = b;
        ring->unk01++;
        if (c == 1)
            a += 256;
        else if (c < 1)
            a -= 256;
        else if (c == 2)
            b -= 256;
        else if (c == 3)
            b += 256;
        i++;
    } while (i <= 15);
}
