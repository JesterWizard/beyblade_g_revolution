#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035054
/* match-compiler: old_agbcc */
// Start one of the three resource animations (kind 0/1/2 -> state slots at
// +0x1C/+0xF8/+0x1D4) for resource `index`: create the anim object, record its
// palette slot in unk3A bits 1.., set the kind's bit in unk2C5 and notify
// sub_08035624 with the resource type.
//
// The nested `do { } while (0)` around the src load is load-bearing. It gives
// `src` loop-depth-weighted refs (11 vs `pos`'s 9), so global alloc gives src r7
// and pos r8 as retail does. Without it the two registers swap and the code
// grows by 8 bytes.
void sub_08035054(void *arg, u32 kindArg, u32 indexArg, s32 value)
{
    struct Unk35258 *state = arg;
    u8 kind = kindArg;
    u8 index = indexArg;
    struct Unk67BB8Source *src = NULL;
    s32 pos = 0;
    u16 id;
    s8 type = 0;

    if (index <= 0x0F)
    {
        do { do { src = gData_080785C8[index]; } while (0); } while (0);
        type = gData_08078608[index];
    }
    switch (kind)
    {
    case 0:
        if ((state->unk2C5 & 1) || index == 0x0E || src == NULL)
            break;
        AnimObjCreate((struct AnimObj *)&state->unk1C, src, 0, 0, pos, pos, value);
        state->unk2B0 = pos;
        state->unk2B4 = pos;
        id = PaletteSlotAcquire(src);
        state->unk1C.unk3A = (state->unk1C.unk3A & 1) | (id << 1);
        state->unk2C5 |= 1;
        sub_08035624((struct Unk346C0 *)state, 0, type);
        break;
    case 1:
        if (state->unk2C5 & 2)
            break;
        AnimObjCreate((struct AnimObj *)&state->unkF8, src, 0, 0, pos, pos, value);
        id = PaletteSlotAcquire(src);
        state->unkF8.unk3A = (state->unkF8.unk3A & 1) | (id << 1);
        state->unk2C5 |= 2;
        sub_08035624((struct Unk346C0 *)state, 1, type);
        break;
    case 2:
        if (state->unk2C5 & 4)
        {
            BattleAnimStop(state, 2);
            if (state->unk2C5 & 4)
                break;
        }
        AnimObjCreate((struct AnimObj *)&state->unk1D4, src, 0, 0, pos, pos, value);
        id = PaletteSlotAcquire(src);
        state->unk1D4.unk3A = (state->unk1D4.unk3A & 1) | (id << 1);
        state->unk2C5 |= 4;
        sub_08035624((struct Unk346C0 *)state, 2, type);
        break;
    }
}

