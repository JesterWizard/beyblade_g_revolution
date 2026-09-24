#include "global.h"
#include "ram_map.h"
#include "battle.h"

extern void sub_080428C4(void);

// @ 0x080428f0
void sub_080428F0(u32 a, u32 b, u32 c, u32 d)
{
    struct Unk0538 *ring;
    struct Unk0538 **ringSlot;
    s32 i;
    u32 step;
    u32 stepBack;


    if (gMainWorkPtr->unk1808 & 0x2000)
        return;
    sub_080428C4();
    i = 0;
    stepBack = 0xFFFFFF00;
    step = 0x100;
    ringSlot = &gUnk_03000538;
    do
    {
        ring = *ringSlot;
        ring->unk04[i] = (u16)d;
        ring->unk44[i] = a;
        ring->unkC4[i] = b;
        ring->unk01++;
        switch (c)
        {
        case 0:
            a += stepBack;
            break;
        case 1:
            a += step;
            break;
        case 2:
            b += stepBack;
            break;
        case 3:
            b += step;
            break;
        }
        i++;
    } while (i <= 15);
}
