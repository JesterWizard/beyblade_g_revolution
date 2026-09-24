#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080442fc
#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

void sub_080442FC(struct Unk442FC *a, struct Unk442FCInput *b, u32 c, u32 d)
{
    u32 index;
    u32 flag;
    u32 *indexp;
    u32 arg4;
    struct Unk442FC *obj;
    u32 mw;
    u32 slot;
    u32 p181b;
    u32 arg2;
    u32 base;
    u32 scaled;
    u32 byte;

    index = 0;
    flag = c;
    arg4 = d;
    obj = a;
    if (b != 0)
    {
        index = b->unk16;
        gMainWorkPtr->unk181B = (u8)Unk84FindIndexByKey(
            (struct Unk6F1A0 *)gData_08091208,
            b->unk14,
            gData_08091204[0]);
    }
    if (obj->unk84 >= 0)
        sub_0806D958((struct Unk6D958 *)obj);
    mw = *(u32 *)gMainWorkPtrLoc;
    slot = mw + 0x1690;
    p181b = mw + 0x181B;
    byte = *(u8 *)p181b;
    scaled = byte << 5;
    scaled += byte;
    indexp = &index;
    scaled <<= 2;
    base = (u32)gData_08091208;
    scaled += base;
    *(u32 *)slot = scaled;
    arg2 = 0x82;
    arg2 <<= 5;
    index <<= 16;
    byte = (*indexp) >> 16;
    sub_08043C70(obj, (void *)scaled, arg2, byte, arg4);
    if (flag != 0)
        sub_0806C78C((void *)sub_08062A14(), obj, (s32)(*indexp) >> 16);
}

