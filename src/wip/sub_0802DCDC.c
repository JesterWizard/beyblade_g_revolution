#include "global.h"

void *sub_08042B00(s16 a);

struct Unk42E78Result
{
    s16 unk00;
    u8 filler_02;
    s8 unk03;
};

void sub_0802DCDC(void *arg)
{
    struct Unk026C *state;
    struct Unk705DC *old_resource;
    struct Unk705DC *resource;
    struct Unk42E78Result *result;
    register struct MainWork **main_loc;
    register struct MainWork *main;
    register u32 flags;
    register u32 mask;
    register struct Unk026C **state_loc;
    register s32 current;
    u16 current_raw;
    register u32 resource_x;
    register u32 resource_y;
    s16 next;
    s32 value;

    main_loc = gMainWorkPtrLoc;
    main = *main_loc;
    flags = main->unk1808;
    if ((flags & 4) != 0)
        return;
    mask = flags & 0x1000;
    if (mask != 0)
        return;
    main->unk1808 = flags | 0x1000;
    current_raw = main->unk1838;
    current = (s16)current_raw;
    if (current == -1)
        return;

    state_loc = &gUnk_0300026C;
    state = *state_loc;
    if ((s8)state->unk48 == -1)
    {
        state->unk4C = current;
        state->unk4E = main->unk183A;
        state->unk48 = 0;
        state->unk04 = 1;
        state->unk44 = arg;
        (*main_loc)->unk16D4 = sub_08042B00(state->unk4E);
        return;
    }
    if (state->unk4C == current)
        return;
    if (state->unk48 != 2)
        return;

    next = main->unk183A;
    result = sub_08042E78(next);
    state = *state_loc;
    old_resource = state->unk28;
    resource_x = old_resource->unk08;
    resource_y = old_resource->unk0C;
    state->unk4C = current_raw;
    state->unk4E = next;
    state->unk44 = arg;
    (*main_loc)->unk16D4 = sub_08042B00(state->unk4E);
    if (state->unk28 != 0)
    {
        sub_0806FE84(state->unk28);
        state->unk28 = (struct Unk705DC *)mask;
    }
    state->unk28 = sub_0806FDD0(1);
    resource = sub_08042B28(state->unk4E);
    sub_0806FF58(
        state->unk28, resource, mask, 1, 1, mask,
        resource_x, resource_y);
    resource = sub_08042B50(state->unk4E);
    _08073C4C(
        resource, (void *)0x05000380, 0x20,
        *(void **)0x080BB8C0);
    sub_080705DC(state->unk28, 0x0C);
    sub_0802E18C(
        (struct Unk310F0b *)state->unk38,
        (struct Unk310F0b *)state->unk3C, (s32)(s8)result->unk03);
    value = (s8)sub_0802E210();
    sub_0802E18C(
        (struct Unk310F0b *)state->unk30,
        (struct Unk310F0b *)state->unk34, value);
    value = sub_0802E1B4((s16)result->unk00);
    state->unk40->unk18 = (s16)(s8)value;
}
