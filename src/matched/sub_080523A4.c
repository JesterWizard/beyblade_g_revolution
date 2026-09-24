#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080523a4
#include "global.h"
#include "ram_map.h"

void sub_080523A4(struct Unk2F520 *a)
{
    struct Unk2F520 *obj;
    struct Unk2F520Inner *slot;
    s8 *flag;
    struct Unk2F520 *alias;
    s32 v;
    u32 base;
    u32 scratch;

    if (obj)
    {
        obj = a;
        sub_08061BE8();
        sub_0805264C(obj, 0);
        sub_0805264C(obj, 1);
        sub_0805264C(obj, 2);
        sub_0805264C(obj, 3);
        sub_0805264C(obj, 4);
        sub_0805264C(obj, 5);
        slot = obj->unk288;
        scratch = 0;
        flag = &(alias = obj)->unk2D5;
        v = *flag;
        v <<= 12;
        base = 0xB0;
        base <<= 6;
        slot->unk0C = v + base + scratch;
        obj = (struct Unk2F520 *)((u32)obj + (0xA3 << 2));
        slot = *(struct Unk2F520Inner **)obj;
        v = *flag;
        v <<= 12;
        slot->unk0C = base + v;
    }
    else
    {
        obj = a;
        sub_08061BE8();
        sub_0805264C(obj, 0);
        sub_0805264C(obj, 1);
        sub_0805264C(obj, 2);
        sub_0805264C(obj, 3);
        sub_0805264C(obj, 4);
        sub_0805264C(obj, 5);
        slot = obj->unk288;
        scratch = 0;
        flag = &(alias = obj)->unk2D5;
        v = *flag;
        v <<= 12;
        base = 0xB0;
        base <<= 6;
        slot->unk0C = v + base + scratch;
        obj = (struct Unk2F520 *)((u32)obj + (0xA3 << 2));
        slot = *(struct Unk2F520Inner **)obj;
        v = *flag;
        v <<= 12;
        slot->unk0C = base + v;
    }
}

