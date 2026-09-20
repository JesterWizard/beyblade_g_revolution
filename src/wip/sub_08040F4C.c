#include "global.h"

void sub_08040F4C(void)
{
    struct Unk40F4C state;
    s32 done;
    register void **target asm("r0");
    register u8 *blend_flag asm("r2");
    register void *handler asm("r3");

    done = 0;
    handler = *(void **)0x080BB8BC;
    _08073C4C(
        0,
        &state,
        0x328,
        handler);
    sub_0804109C(&state, sub_0806639C());
    sub_08060468();
    sub_08060758();

    do
    {
        sub_080604C8();
        sub_080607BC();
        sub_080674B4();
        sub_0806A6F8();
        if ((state.unk324 & 1) == 0)
            _08073C40(*(void **)0x080BB888);

        blend_flag = &state.unk2D7;
        if (*blend_flag == 1)
        {
            switch (state.unk322)
            {
            case 1:
                state.unk31C -= state.unk31E;
                if ((s16)state.unk31C < 0)
                {
                    state.unk31C = 0;
                    *blend_flag = 0;
                }
                break;
            case 2:
                state.unk31C += state.unk31E;
                if ((s16)state.unk31C > 0x1F)
                {
                    state.unk31C = 0x1F;
                    *blend_flag = 0;
                }
                break;
            }
            REG_BLDCNT = state.unk320;
            REG_BLDALPHA = state.unk31C;
        }

        switch (state.unk2D4)
        {
        case 0:
            target = &state.unk24C;
            break;
        case 1:
            if (state.unk250 != 0)
                _08073C44(&state, state.unk250);
            sub_080411EC(&state);
            target = 0;
            break;
        case 2:
            target = &state.unk254;
            break;
        case 3:
            done = 1;
            target = 0;
            break;
        default:
            target = 0;
            break;
        }

        if (target != 0 && *target != 0)
            _08073C44(&state, *target);
        if (state.unk258 != 0)
            _08073C44(&state, state.unk258);
    } while (done == 0);

    sub_08041394((struct Unk41394 *)&state);
    sub_080604A4();
    sub_08060798();
}
