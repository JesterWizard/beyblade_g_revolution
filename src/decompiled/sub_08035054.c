/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void sub_08035054(void *arg, u32 kindArg, u32 indexArg, s32 value)
{
    struct Unk35258 *state = arg;
    u8 kind = kindArg;
    u8 index = indexArg;
    s32 pos = 0;
    struct Unk67BB8Source *src = NULL;
    s8 type = 0;
    u16 id;

    if (index <= 0x0F)
    {
        src = gData_080785C8[index];
        type = gData_08078608[index];
    }
    switch (kind)
    {
    case 0:
        if ((state->unk2C5 & 1) || index == 0x0E || src == NULL)
            break;
        sub_08067BB8((struct Unk67BB8 *)&state->unk1C, src, 0, 0, pos, pos, value);
        state->unk2B0 = pos;
        state->unk2B4 = pos;
        id = sub_08038438(src);
        state->unk1C.unk3A = (state->unk1C.unk3A & 1) | (id << 1);
        state->unk2C5 |= 1;
        sub_08035624((struct Unk346C0 *)state, 0, type);
        break;
    case 1:
        if (state->unk2C5 & 2)
            break;
        sub_08067BB8((struct Unk67BB8 *)&state->unkF8, src, 0, 0, pos, pos, value);
        id = sub_08038438(src);
        state->unkF8.unk3A = (state->unkF8.unk3A & 1) | (id << 1);
        state->unk2C5 |= 2;
        sub_08035624((struct Unk346C0 *)state, 1, type);
        break;
    case 2:
        if (state->unk2C5 & 4)
        {
            sub_08035258(state, 2);
            if (state->unk2C5 & 4)
                break;
        }
        sub_08067BB8((struct Unk67BB8 *)&state->unk1D4, src, 0, 0, pos, pos, value);
        id = sub_08038438(src);
        state->unk1D4.unk3A = (state->unk1D4.unk3A & 1) | (id << 1);
        state->unk2C5 |= 4;
        sub_08035624((struct Unk346C0 *)state, 2, type);
        break;
    }

}
