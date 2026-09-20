#include "global.h"

void sub_08067BB8(
    void *a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
u32 sub_08038438(void *a);
void sub_08035624(void *a, s32 b, s32 c);

struct Unk35054
{
    u8 filler_00[0x1C];
    u8 unk01C[0x3A];
    u8 unk56;
    u8 filler_57[0xA1];
    u8 unk0F8[0x3A];
    u8 unk132;
    u8 filler_133[0xA1];
    u8 unk1D4[0x3A];
    u8 unk20E;
    u8 filler_20F[0xA1];
    u32 unk2B0;
    u32 unk2B4;
    u8 filler_2B8[0x0D];
    u8 unk2C5;
};

void sub_08035054(void *arg, u32 type_arg, u32 index_arg, s32 value_arg)
{
    struct Unk35054 *state;
    s32 value;
    u8 kind;
    u8 index;
    void *resource;
    u8 resource_type;
    u32 resource_id;

    state = (struct Unk35054 *)arg;
    value = value_arg;
    kind = (u8)type_arg;
    index = (u8)index_arg;
    resource = 0;
    resource_type = 0;
    if (index <= 0x0F)
    {
        resource = ((void **)0x080785C8)[index];
        resource_type = ((u8 *)0x08078608)[index];
    }
    if (kind == 0)
    {
        if ((state->unk2C5 & 1) != 0)
            return;
        if (index == 0x0E)
            return;
        if (resource == 0)
            return;
        sub_08067BB8(
            state->unk01C, resource, 0, 0, 0, 0, value);
        state->unk2B0 = 0;
        state->unk2B4 = 0;
        resource_id = (u16)sub_08038438(resource);
        state->unk56 =
            (state->unk56 & 1) | ((u16)resource_id << 1);
        state->unk2C5 |= 1;
        sub_08035624(state, (s8)resource_type, 0);
    }
    else if (kind == 1)
    {
        if ((state->unk2C5 & 2) != 0)
            return;
        sub_08067BB8(
            state->unk0F8, resource, 0, 0, 0, 0, value);
        resource_id = (u16)sub_08038438(resource);
        state->unk132 =
            (state->unk132 & kind) | ((u16)resource_id << 1);
        state->unk2C5 |= 2;
        sub_08035624(state, (s8)resource_type, 1);
    }
    else if (kind == 2)
    {
        if ((state->unk2C5 & 4) != 0)
        {
            sub_08035258((struct Unk35258 *)state, 2);
            if ((state->unk2C5 & 4) != 0)
                return;
        }
        sub_08067BB8(
            state->unk1D4, resource, 0, 0, 0, 0, value);
        resource_id = (u16)sub_08038438(resource);
        state->unk20E =
            (state->unk20E & 1) | ((u16)resource_id << 1);
        state->unk2C5 |= 4;
        sub_08035624(state, (s8)resource_type, 2);
    }
}
